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
struct TYPE_4__ {int content_length; scalar_t__ transfer; int buffer_end; int buffer_start; char* buffer; size_t chunked_offset; int /*<<< orphan*/  protocol; int /*<<< orphan*/  on_error; int /*<<< orphan*/  on_body; int /*<<< orphan*/  request; int /*<<< orphan*/  chunked_decoder; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Parser ;

/* Variables and functions */
 int CONTENT_LENGTH_UNSET ; 
 scalar_t__ PARSER_CHUNKED ; 
 scalar_t__ PARSER_TRANSFER_UNSET ; 
 int /*<<< orphan*/  Protocol_on_body (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  Protocol_on_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyBUF_READ ; 
 int /*<<< orphan*/ * PyMemoryView_FromMemory (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyObject_Print (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PyObject_SetAttrString (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _reset_state (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * malformed_body ; 
 int phr_decode_chunked (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ zero_body ; 

__attribute__((used)) static int _parse_body(Parser* self) {
#ifdef PARSER_STANDALONE
  PyObject* body_view = NULL;
#endif

  char* body = NULL;
  size_t body_len = 0;
  int result = -2;
  if(self->content_length == CONTENT_LENGTH_UNSET
     && self->transfer == PARSER_TRANSFER_UNSET) {
    result = 0;
    goto on_body;
  }

  if(self->content_length == 0) {
    body = (char*)zero_body;
    result = 0;
    goto on_body;
  }

  if(self->content_length != CONTENT_LENGTH_UNSET) {
    if(self->content_length > self->buffer_end - self->buffer_start) {
      result = -2;
      goto finally;
    }

    body = self->buffer + self->buffer_start;
    body_len = self->content_length;

    self->buffer_start += self->content_length;

    // TODO result = self->content_length (long)
    result = 1;

    goto on_body;
  }

  if(self->transfer == PARSER_CHUNKED) {
    size_t chunked_offset_start = self->chunked_offset;
    self->chunked_offset = self->buffer_end - self->buffer_start - self->chunked_offset;
    result = phr_decode_chunked(
      &self->chunked_decoder,
      self->buffer + self->buffer_start + chunked_offset_start,
      &self->chunked_offset);
    self->chunked_offset = self->chunked_offset + chunked_offset_start;

    if(result == -2) {
      self->buffer_end = self->buffer_start + self->chunked_offset;
      goto finally;
    }

    if(result == -1)
      goto on_error;

    body = self->buffer + self->buffer_start;
    body_len = self->chunked_offset;

    self->buffer_start += self->chunked_offset;
    self->buffer_end = self->buffer_start + (size_t)result;

    goto on_body;
  }

  goto finally;

  on_body:

  if(body) {
#if 0
    if(PyObject_SetAttrString(self->request, "body", body) == -1) {
      result = -3;
      goto finally;
    }
#else
    /*((Request*)(self->request))->body = body;
    Py_INCREF(body);*/
#endif

#ifdef DEBUG_PRINT
    printf("body: "); PyObject_Print(body, stdout, 0); printf("\n");
#endif
  }

#ifdef PARSER_STANDALONE
  if(body) {
    body_view = PyMemoryView_FromMemory(body, body_len, PyBUF_READ);
    if(!body_view)
      goto error;
  } else {
    body_view = Py_None;
    Py_INCREF(body_view);
  }
  PyObject* on_body_result = PyObject_CallFunctionObjArgs(
    self->on_body, body_view, NULL);
  if(!on_body_result)
    goto error;
  Py_DECREF(on_body_result);
#else
  if(!Protocol_on_body(self->protocol, body, body_len, self->buffer_end - self->buffer_start))
    goto error;
#endif

  _reset_state(self, false);

  goto finally;

#ifdef PARSER_STANDALONE
  PyObject* on_error_result;
  on_error:
  on_error_result = PyObject_CallFunctionObjArgs(
    self->on_error, malformed_body, NULL);
  if(!on_error_result)
    goto error;
  Py_DECREF(on_error_result);
#else
  on_error:
  if(!Protocol_on_error(self->protocol, malformed_body))
    goto error;
#endif

  _reset_state(self, true);

  result = -1;

  goto finally;

  error:
  result = -3;

  finally:
#ifdef PARSER_STANDALONE
  Py_XDECREF(body_view);
#endif
  return result;
}