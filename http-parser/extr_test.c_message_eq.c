#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct message {scalar_t__ type; int status_cb_called; int message_begin_cb_called; int headers_complete_cb_called; int message_complete_cb_called; char* request_url; scalar_t__ method; int body_size; int num_chunks_complete; int num_chunks; int num_headers; int /*<<< orphan*/ ** headers; int /*<<< orphan*/  port; scalar_t__ userinfo; scalar_t__ host; } ;
struct http_parser_url {int field_set; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ HTTP_CONNECT ; 
 scalar_t__ HTTP_REQUEST ; 
 int MAX_CHUNKS ; 
 int /*<<< orphan*/  MESSAGE_CHECK_NUM_EQ (struct message const*,struct message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESSAGE_CHECK_STR_EQ (struct message const*,struct message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESSAGE_CHECK_URL_EQ (struct http_parser_url*,struct message const*,struct message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UF_FRAGMENT ; 
 int /*<<< orphan*/  UF_HOST ; 
 int /*<<< orphan*/  UF_PATH ; 
 int UF_PORT ; 
 int /*<<< orphan*/  UF_QUERY ; 
 int /*<<< orphan*/  UF_USERINFO ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  body ; 
 int /*<<< orphan*/  body_size ; 
 int /*<<< orphan*/  check_num_eq (struct message*,char*,int /*<<< orphan*/ ,int) ; 
 int check_str_eq (struct message const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * chunk_lengths ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fragment ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  http_major ; 
 int /*<<< orphan*/  http_minor ; 
 scalar_t__ http_parser_parse_url (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct http_parser_url*) ; 
 int /*<<< orphan*/  message_complete_on_eof ; 
 struct message* messages ; 
 int /*<<< orphan*/  method ; 
 int /*<<< orphan*/  num_chunks_complete ; 
 int /*<<< orphan*/  num_headers ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  query_string ; 
 int /*<<< orphan*/  request_path ; 
 int /*<<< orphan*/  request_url ; 
 int /*<<< orphan*/  response_status ; 
 int /*<<< orphan*/  should_keep_alive ; 
 int /*<<< orphan*/  status_code ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  upgrade ; 
 int /*<<< orphan*/  userinfo ; 

int
message_eq (int index, int connect, const struct message *expected)
{
  int i;
  struct message *m = &messages[index];

  MESSAGE_CHECK_NUM_EQ(expected, m, http_major);
  MESSAGE_CHECK_NUM_EQ(expected, m, http_minor);

  if (expected->type == HTTP_REQUEST) {
    MESSAGE_CHECK_NUM_EQ(expected, m, method);
  } else {
    MESSAGE_CHECK_NUM_EQ(expected, m, status_code);
    MESSAGE_CHECK_STR_EQ(expected, m, response_status);
    assert(m->status_cb_called);
  }

  if (!connect) {
    MESSAGE_CHECK_NUM_EQ(expected, m, should_keep_alive);
    MESSAGE_CHECK_NUM_EQ(expected, m, message_complete_on_eof);
  }

  assert(m->message_begin_cb_called);
  assert(m->headers_complete_cb_called);
  assert(m->message_complete_cb_called);


  MESSAGE_CHECK_STR_EQ(expected, m, request_url);

  /* Check URL components; we can't do this w/ CONNECT since it doesn't
   * send us a well-formed URL.
   */
  if (*m->request_url && m->method != HTTP_CONNECT) {
    struct http_parser_url u;

    if (http_parser_parse_url(m->request_url, strlen(m->request_url), 0, &u)) {
      fprintf(stderr, "\n\n*** failed to parse URL %s ***\n\n",
        m->request_url);
      abort();
    }

    if (expected->host) {
      MESSAGE_CHECK_URL_EQ(&u, expected, m, host, UF_HOST);
    }

    if (expected->userinfo) {
      MESSAGE_CHECK_URL_EQ(&u, expected, m, userinfo, UF_USERINFO);
    }

    m->port = (u.field_set & (1 << UF_PORT)) ?
      u.port : 0;

    MESSAGE_CHECK_URL_EQ(&u, expected, m, query_string, UF_QUERY);
    MESSAGE_CHECK_URL_EQ(&u, expected, m, fragment, UF_FRAGMENT);
    MESSAGE_CHECK_URL_EQ(&u, expected, m, request_path, UF_PATH);
    MESSAGE_CHECK_NUM_EQ(expected, m, port);
  }

  if (connect) {
    check_num_eq(m, "body_size", 0, m->body_size);
  } else if (expected->body_size) {
    MESSAGE_CHECK_NUM_EQ(expected, m, body_size);
  } else {
    MESSAGE_CHECK_STR_EQ(expected, m, body);
  }

  if (connect) {
    check_num_eq(m, "num_chunks_complete", 0, m->num_chunks_complete);
  } else {
    assert(m->num_chunks == m->num_chunks_complete);
    MESSAGE_CHECK_NUM_EQ(expected, m, num_chunks_complete);
    for (i = 0; i < m->num_chunks && i < MAX_CHUNKS; i++) {
      MESSAGE_CHECK_NUM_EQ(expected, m, chunk_lengths[i]);
    }
  }

  MESSAGE_CHECK_NUM_EQ(expected, m, num_headers);

  int r;
  for (i = 0; i < m->num_headers; i++) {
    r = check_str_eq(expected, "header field", expected->headers[i][0], m->headers[i][0]);
    if (!r) return 0;
    r = check_str_eq(expected, "header value", expected->headers[i][1], m->headers[i][1]);
    if (!r) return 0;
  }

  if (!connect) {
    MESSAGE_CHECK_STR_EQ(expected, m, upgrade);
  }

  return 1;
}