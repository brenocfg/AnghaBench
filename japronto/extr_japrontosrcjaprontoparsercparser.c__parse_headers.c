#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct phr_header {scalar_t__ name_len; char* name; scalar_t__ value_len; char* value; } ;
typedef  int /*<<< orphan*/  headers ;
struct TYPE_4__ {scalar_t__ connection; int /*<<< orphan*/  protocol; scalar_t__ buffer_start; int /*<<< orphan*/  content_length; int /*<<< orphan*/  transfer; scalar_t__ buffer_end; scalar_t__ buffer; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Parser ;

/* Variables and functions */
 int /*<<< orphan*/  PARSER_CHUNKED ; 
 scalar_t__ PARSER_CLOSE ; 
 int /*<<< orphan*/  PARSER_IDENTITY ; 
 void* PARSER_KEEP_ALIVE ; 
 int /*<<< orphan*/  Protocol_on_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Protocol_on_headers (int /*<<< orphan*/ ,char*,size_t,char*,size_t,int,struct phr_header*,size_t) ; 
 int _phr_parse_request (scalar_t__,scalar_t__,char const**,size_t*,char const**,size_t*,int*,struct phr_header*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _reset_state (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * excessive_data ; 
 int /*<<< orphan*/ * invalid_headers ; 
 int /*<<< orphan*/ * malformed_headers ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static int _parse_headers(Parser* self) {
#ifdef PARSER_STANDALONE
  PyObject* method_view = NULL;
  PyObject* path_view = NULL;
  PyObject* minor_version_long = NULL;
  PyObject* headers_view = NULL;
#endif
  PyObject* error;

  int result = -1;
  if(self->connection == PARSER_CLOSE) {
    error = excessive_data;
    goto on_error;
  }

  char* method;
  size_t method_len;
  char* path;
  size_t path_len;
  int minor_version;
  struct phr_header headers[50];
  size_t num_headers = sizeof(headers) / sizeof(struct phr_header);

  result = _phr_parse_request(
    self->buffer + self->buffer_start, self->buffer_end - self->buffer_start,
    (const char**)&method, &method_len,
    (const char**)&path, &path_len,
    &minor_version, headers, &num_headers, 0);

  // FIXME: More than 10 headers
#ifdef DEBUG_PRINT
  printf("result: %d\n", result);
#endif

  if(result == -2)
    goto finally;

  if(result == -1) {
    error = malformed_headers;
    goto on_error;
  }

  if(minor_version == 0) {
    self->connection = PARSER_CLOSE;
  } else {
    self->connection = PARSER_KEEP_ALIVE;
  }

#define header_name_equal(val) \
  header->name_len == strlen(val) && strncasecmp(header->name, val, header->name_len) == 0
#define header_value_equal(val) \
  header->value_len == strlen(val) && strncasecmp(header->value, val, header->value_len) == 0
/*#define cmp_and_set_header_name(name, val) \
  if(header_name_equal(val)) { \
      py_header_name = name; \
      Py_INCREF(name); \
  }
#define cmp_and_set_header_value(name, val) \
  if(header_value_equal(val)) { \
      py_header_value = name; \
      Py_INCREF(name); \
  }*/

  for(struct phr_header* header = headers;
      header < headers + num_headers;
      header++) {

    // TODO: common names and values static
    /*PyObject* py_header_name = NULL;
    PyObject* py_header_value = NULL;*/

    if(header_name_equal("Transfer-Encoding")) {
      if(header_value_equal("chunked"))
        self->transfer = PARSER_CHUNKED;
      else if(header_value_equal("identity"))
        self->transfer = PARSER_IDENTITY;
      else
        /*TODO: handle incorrept values for protocol version, also comma sep*/;

      /*py_header_name = Transfer_Encoding;
      Py_INCREF(Transfer_Encoding);*/
    } else if(header_name_equal("Content-Length")) {
      if(!header->value_len) {
        error = invalid_headers;
        goto on_error;
      }

      if(*header->value == '+' || *header->value == '-') {
        error = invalid_headers;
        goto on_error;
      }

      char * endptr = (char *)header->value + header->value_len;
      self->content_length = strtol(header->value, &endptr, 10);
      // FIXME: overflow?

      if(endptr != (char*)header->value + header->value_len) {
        error = invalid_headers;
        goto on_error;
      }
    } else if(header_name_equal("Connection")) {
      if(header_value_equal("close"))
        self->connection = PARSER_CLOSE;
      else if(header_value_equal("keep-alive"))
        self->connection = PARSER_KEEP_ALIVE;
      else
        /* FIXME: on_error*/;
      /*py_header_name = Content_Length;
      Py_INCREF(Content_Length);*/
    }
    /*else cmp_and_set_header_name(Host, "Host")
    else cmp_and_set_header_name(User_Agent, "User-Agent")
    else cmp_and_set_header_name(Accept, "Accept")
    else cmp_and_set_header_name(Accept_Language, "Accept-Language")
    else cmp_and_set_header_name(Accept_Encoding, "Accept-Encoding")
    else cmp_and_set_header_name(Accept_Charset, "Accept-Charset")
    else cmp_and_set_header_name(Connection, "Connection")
    else cmp_and_set_header_name(Cookie, "Cookie")
    else {
      bool prev_alpha = false;
      for(char* c = (char*)header.name; c < header.name + header.name_len; c++) {
        if(*c >= 'A' && *c <= 'Z') {
          if(prev_alpha)
            *c |= 0x20;
          prev_alpha = true;
        } else if (*c >= 'a' && *c <= 'z')
          prev_alpha = true;
        else
          prev_alpha = false;
      }

      // FIXME this should accept only ascii
      py_header_name = PyUnicode_FromStringAndSize(
        header.name, header.name_len);
      if(!py_header_name) {
        result = -3;
        goto finally_loop;
      }
    }

    if(py_header_name == Connection) {
      cmp_and_set_header_value(keep_alive, "keep-alive")
      else cmp_and_set_header_value(val_close, "close")
      else FIXME: invalid Connection value;
    } else {
      // FIXME: this can return NULL on codec error
      py_header_value = PyUnicode_DecodeLatin1(
        header.value, header.value_len, NULL);
      if(!py_header_value) {
        result = -3;
        goto finally_loop;
      }
    }

    if(PyDict_SetItem(py_headers, py_header_name, py_header_value) == -1)
      result = -3;

#ifdef DEBUG_PRINT
    PyObject_Print(py_header_name, stdout, 0); printf(": ");
    PyObject_Print(py_header_value, stdout, 0); printf("\n");
#endif

    finally_loop:
    Py_XDECREF(py_header_value);
    Py_XDECREF(py_header_name);

    if(result == -3)
      goto finally;*/
  }

#ifdef DEBUG_PRINT
  if(self->content_length != CONTENT_LENGTH_UNSET)
    printf("self->content_length: %ld\n", self->content_length);
  if(self->transfer == PARSER_IDENTITY)
    printf("self->transfer: identity\n");
  else if(self->transfer == PARSER_CHUNKED)
    printf("self->transfer: chunked\n");
#endif

#ifdef PARSER_STANDALONE
  method_view = PyMemoryView_FromMemory(method, method_len, PyBUF_READ);
  path_view = PyMemoryView_FromMemory(path, path_len, PyBUF_READ);
  minor_version_long = PyLong_FromLong(minor_version);
  headers_view = PyMemoryView_FromMemory((char*)headers, sizeof(struct phr_header) * num_headers, PyBUF_READ);
  // FIXME the functions above can fail
  PyObject* on_headers_result = PyObject_CallFunctionObjArgs(
    self->on_headers, method_view, path_view, minor_version_long, headers_view, NULL);
  if(!on_headers_result)
    goto error;
  Py_DECREF(on_headers_result);
#else
  if(!Protocol_on_headers(
      self->protocol, method, method_len,
      path, path_len, minor_version, headers, num_headers))
    goto error;
#endif

  self->buffer_start += (size_t)result;

  goto finally;

#ifdef PARSER_STANDALONE
  PyObject* on_error_result;
  on_error:
  on_error_result = PyObject_CallFunctionObjArgs(
    self->on_error, error, NULL);
  if(!on_error_result)
    goto error;
  Py_DECREF(on_error_result);
#else
  on_error:
  if(!Protocol_on_error(self->protocol, error))
    goto error;
#endif

  _reset_state(self, true);

  result = -1;

  goto finally;

  error:
  result = -3;

  finally:
#ifdef PARSER_STANDALONE
  Py_XDECREF(headers_view);
  Py_XDECREF(minor_version_long);
  Py_XDECREF(path_view);
  Py_XDECREF(method_view);
#endif

  return result;
}