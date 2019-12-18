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
struct message {char* name; char* raw; int http_major; int status_code; char* response_status; int num_headers; int body_size; int num_chunks_complete; int* chunk_lengths; int /*<<< orphan*/  should_keep_alive; int /*<<< orphan*/  headers; int /*<<< orphan*/  http_minor; int /*<<< orphan*/  message_complete_on_eof; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  http_parser ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct message*) ; 
 size_t BONJOUR_MADAME_FR ; 
 size_t CHUNKED_W_NONSENSE_AFTER_LENGTH ; 
 size_t CHUNKED_W_TRAILING_HEADERS ; 
 size_t CONNECT_REQUEST ; 
 int /*<<< orphan*/  FALSE ; 
 size_t GET_FUNKY_CONTENT_LENGTH ; 
 size_t GET_NO_HEADERS_NO_BODY ; 
 size_t GET_ONE_HEADER_NO_BODY ; 
 int /*<<< orphan*/  HPE_INVALID_CONSTANT ; 
 int /*<<< orphan*/  HPE_INVALID_CONTENT_LENGTH ; 
 int /*<<< orphan*/  HPE_INVALID_HEADER_TOKEN ; 
 int /*<<< orphan*/  HPE_INVALID_METHOD ; 
 int /*<<< orphan*/  HPE_INVALID_VERSION ; 
 int /*<<< orphan*/  HPE_OK ; 
 int /*<<< orphan*/  HTTP_REQUEST ; 
 int /*<<< orphan*/  HTTP_RESPONSE ; 
 unsigned int MAX_CHUNKS ; 
 size_t NO_BODY_HTTP10_KA_204 ; 
 size_t NO_CARRIAGE_RET ; 
 size_t NO_HEADERS_NO_BODY_404 ; 
 size_t NO_REASON_PHRASE ; 
 size_t POST_CHUNKED_ALL_YOUR_BASE ; 
 size_t POST_IDENTITY_BODY_WORLD ; 
 size_t PREFIX_NEWLINE_GET ; 
 size_t QUERY_URL_WITH_QUESTION_MARK_GET ; 
 size_t TRAILING_SPACE_ON_CHUNKED_BODY ; 
 size_t TWO_CHUNKS_MULT_ZERO_END ; 
 size_t UNDERSTORE_HEADER_KEY ; 
 char* create_large_chunked_message (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 unsigned long http_parser_version () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 struct message* requests ; 
 struct message* responses ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  test_chunk_content_length_overflow_error () ; 
 int /*<<< orphan*/  test_chunked_content_length_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_double_content_length_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_header_content_length_overflow_error () ; 
 int /*<<< orphan*/  test_header_cr_no_lf_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_header_nread_value () ; 
 int /*<<< orphan*/  test_header_overflow_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_invalid_header_field_content_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_invalid_header_field_token_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_message (struct message*) ; 
 int /*<<< orphan*/  test_message_connect (struct message*) ; 
 int /*<<< orphan*/  test_message_count_body (struct message*) ; 
 int /*<<< orphan*/  test_message_pause (struct message*) ; 
 int /*<<< orphan*/  test_method_str () ; 
 int /*<<< orphan*/  test_multiple3 (struct message*,struct message*,struct message*) ; 
 int /*<<< orphan*/  test_no_overflow_long_body (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_no_overflow_parse_url () ; 
 int /*<<< orphan*/  test_parse_url () ; 
 int /*<<< orphan*/  test_preserve_data () ; 
 int /*<<< orphan*/  test_scan (struct message*,struct message*,struct message*) ; 
 int /*<<< orphan*/  test_simple (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_simple_type (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_status_str () ; 

int
main (void)
{
  unsigned i, j, k;
  unsigned long version;
  unsigned major;
  unsigned minor;
  unsigned patch;

  version = http_parser_version();
  major = (version >> 16) & 255;
  minor = (version >> 8) & 255;
  patch = version & 255;
  printf("http_parser v%u.%u.%u (0x%06lx)\n", major, minor, patch, version);

  printf("sizeof(http_parser) = %u\n", (unsigned int)sizeof(http_parser));

  //// API
  test_preserve_data();
  test_parse_url();
  test_method_str();
  test_status_str();

  //// NREAD
  test_header_nread_value();

  //// OVERFLOW CONDITIONS
  test_no_overflow_parse_url();

  test_header_overflow_error(HTTP_REQUEST);
  test_no_overflow_long_body(HTTP_REQUEST, 1000);
  test_no_overflow_long_body(HTTP_REQUEST, 100000);

  test_header_overflow_error(HTTP_RESPONSE);
  test_no_overflow_long_body(HTTP_RESPONSE, 1000);
  test_no_overflow_long_body(HTTP_RESPONSE, 100000);

  test_header_content_length_overflow_error();
  test_chunk_content_length_overflow_error();

  //// HEADER FIELD CONDITIONS
  test_double_content_length_error(HTTP_REQUEST);
  test_chunked_content_length_error(HTTP_REQUEST);
  test_header_cr_no_lf_error(HTTP_REQUEST);
  test_invalid_header_field_token_error(HTTP_REQUEST);
  test_invalid_header_field_content_error(HTTP_REQUEST);
  test_double_content_length_error(HTTP_RESPONSE);
  test_chunked_content_length_error(HTTP_RESPONSE);
  test_header_cr_no_lf_error(HTTP_RESPONSE);
  test_invalid_header_field_token_error(HTTP_RESPONSE);
  test_invalid_header_field_content_error(HTTP_RESPONSE);

  test_simple_type(
      "POST / HTTP/1.1\r\n"
      "Content-Length:\r\n"  // empty
      "\r\n",
      HPE_INVALID_CONTENT_LENGTH,
      HTTP_REQUEST);

  test_simple_type(
      "POST / HTTP/1.1\r\n"
      "Content-Length:  42 \r\n"  // Note the surrounding whitespace.
      "\r\n",
      HPE_OK,
      HTTP_REQUEST);

  test_simple_type(
      "POST / HTTP/1.1\r\n"
      "Content-Length: 4 2\r\n"
      "\r\n",
      HPE_INVALID_CONTENT_LENGTH,
      HTTP_REQUEST);

  test_simple_type(
      "POST / HTTP/1.1\r\n"
      "Content-Length: 13 37\r\n"
      "\r\n",
      HPE_INVALID_CONTENT_LENGTH,
      HTTP_REQUEST);

  test_simple_type(
      "POST / HTTP/1.1\r\n"
      "Content-Length:  42\r\n"
      " Hello world!\r\n",
      HPE_INVALID_CONTENT_LENGTH,
      HTTP_REQUEST);

  test_simple_type(
      "POST / HTTP/1.1\r\n"
      "Content-Length:  42\r\n"
      " \r\n",
      HPE_OK,
      HTTP_REQUEST);

  //// RESPONSES

  test_simple_type("HTP/1.1 200 OK\r\n\r\n", HPE_INVALID_VERSION, HTTP_RESPONSE);
  test_simple_type("HTTP/01.1 200 OK\r\n\r\n", HPE_INVALID_VERSION, HTTP_RESPONSE);
  test_simple_type("HTTP/11.1 200 OK\r\n\r\n", HPE_INVALID_VERSION, HTTP_RESPONSE);
  test_simple_type("HTTP/1.01 200 OK\r\n\r\n", HPE_INVALID_VERSION, HTTP_RESPONSE);
  test_simple_type("HTTP/1.1\t200 OK\r\n\r\n", HPE_INVALID_VERSION, HTTP_RESPONSE);
  test_simple_type("\rHTTP/1.1\t200 OK\r\n\r\n", HPE_INVALID_VERSION, HTTP_RESPONSE);

  for (i = 0; i < ARRAY_SIZE(responses); i++) {
    test_message(&responses[i]);
  }

  for (i = 0; i < ARRAY_SIZE(responses); i++) {
    test_message_pause(&responses[i]);
  }

  for (i = 0; i < ARRAY_SIZE(responses); i++) {
    test_message_connect(&responses[i]);
  }

  for (i = 0; i < ARRAY_SIZE(responses); i++) {
    if (!responses[i].should_keep_alive) continue;
    for (j = 0; j < ARRAY_SIZE(responses); j++) {
      if (!responses[j].should_keep_alive) continue;
      for (k = 0; k < ARRAY_SIZE(responses); k++) {
        test_multiple3(&responses[i], &responses[j], &responses[k]);
      }
    }
  }

  test_message_count_body(&responses[NO_HEADERS_NO_BODY_404]);
  test_message_count_body(&responses[TRAILING_SPACE_ON_CHUNKED_BODY]);

  // test very large chunked response
  {
    char * msg = create_large_chunked_message(31337,
      "HTTP/1.0 200 OK\r\n"
      "Transfer-Encoding: chunked\r\n"
      "Content-Type: text/plain\r\n"
      "\r\n");
    struct message large_chunked =
      {.name= "large chunked"
      ,.type= HTTP_RESPONSE
      ,.raw= msg
      ,.should_keep_alive= FALSE
      ,.message_complete_on_eof= FALSE
      ,.http_major= 1
      ,.http_minor= 0
      ,.status_code= 200
      ,.response_status= "OK"
      ,.num_headers= 2
      ,.headers=
        { { "Transfer-Encoding", "chunked" }
        , { "Content-Type", "text/plain" }
        }
      ,.body_size= 31337*1024
      ,.num_chunks_complete= 31338
      };
    for (i = 0; i < MAX_CHUNKS; i++) {
      large_chunked.chunk_lengths[i] = 1024;
    }
    test_message_count_body(&large_chunked);
    free(msg);
  }



  printf("response scan 1/2      ");
  test_scan( &responses[TRAILING_SPACE_ON_CHUNKED_BODY]
           , &responses[NO_BODY_HTTP10_KA_204]
           , &responses[NO_REASON_PHRASE]
           );

  printf("response scan 2/2      ");
  test_scan( &responses[BONJOUR_MADAME_FR]
           , &responses[UNDERSTORE_HEADER_KEY]
           , &responses[NO_CARRIAGE_RET]
           );

  puts("responses okay");


  /// REQUESTS

  test_simple("GET / IHTTP/1.0\r\n\r\n", HPE_INVALID_CONSTANT);
  test_simple("GET / ICE/1.0\r\n\r\n", HPE_INVALID_CONSTANT);
  test_simple("GET / HTP/1.1\r\n\r\n", HPE_INVALID_VERSION);
  test_simple("GET / HTTP/01.1\r\n\r\n", HPE_INVALID_VERSION);
  test_simple("GET / HTTP/11.1\r\n\r\n", HPE_INVALID_VERSION);
  test_simple("GET / HTTP/1.01\r\n\r\n", HPE_INVALID_VERSION);

  test_simple("GET / HTTP/1.0\r\nHello: w\1rld\r\n\r\n", HPE_INVALID_HEADER_TOKEN);
  test_simple("GET / HTTP/1.0\r\nHello: woooo\2rld\r\n\r\n", HPE_INVALID_HEADER_TOKEN);

  // Extended characters - see nodejs/test/parallel/test-http-headers-obstext.js
  test_simple("GET / HTTP/1.1\r\n"
              "Test: Düsseldorf\r\n",
              HPE_OK);

  // Well-formed but incomplete
  test_simple("GET / HTTP/1.1\r\n"
              "Content-Type: text/plain\r\n"
              "Content-Length: 6\r\n"
              "\r\n"
              "fooba",
              HPE_OK);

  static const char *all_methods[] = {
    "DELETE",
    "GET",
    "HEAD",
    "POST",
    "PUT",
    //"CONNECT", //CONNECT can't be tested like other methods, it's a tunnel
    "OPTIONS",
    "TRACE",
    "COPY",
    "LOCK",
    "MKCOL",
    "MOVE",
    "PROPFIND",
    "PROPPATCH",
    "SEARCH",
    "UNLOCK",
    "BIND",
    "REBIND",
    "UNBIND",
    "ACL",
    "REPORT",
    "MKACTIVITY",
    "CHECKOUT",
    "MERGE",
    "M-SEARCH",
    "NOTIFY",
    "SUBSCRIBE",
    "UNSUBSCRIBE",
    "PATCH",
    "PURGE",
    "MKCALENDAR",
    "LINK",
    "UNLINK",
    0 };
  const char **this_method;
  for (this_method = all_methods; *this_method; this_method++) {
    char buf[200];
    sprintf(buf, "%s / HTTP/1.1\r\n\r\n", *this_method);
    test_simple(buf, HPE_OK);
  }

  static const char *bad_methods[] = {
      "ASDF",
      "C******",
      "COLA",
      "GEM",
      "GETA",
      "M****",
      "MKCOLA",
      "PROPPATCHA",
      "PUN",
      "PX",
      "SA",
      "hello world",
      0 };
  for (this_method = bad_methods; *this_method; this_method++) {
    char buf[200];
    sprintf(buf, "%s / HTTP/1.1\r\n\r\n", *this_method);
    test_simple(buf, HPE_INVALID_METHOD);
  }

  // illegal header field name line folding
  test_simple("GET / HTTP/1.1\r\n"
              "name\r\n"
              " : value\r\n"
              "\r\n",
              HPE_INVALID_HEADER_TOKEN);

  const char *dumbluck2 =
    "GET / HTTP/1.1\r\n"
    "X-SSL-Nonsense:   -----BEGIN CERTIFICATE-----\r\n"
    "\tMIIFbTCCBFWgAwIBAgICH4cwDQYJKoZIhvcNAQEFBQAwcDELMAkGA1UEBhMCVUsx\r\n"
    "\tETAPBgNVBAoTCGVTY2llbmNlMRIwEAYDVQQLEwlBdXRob3JpdHkxCzAJBgNVBAMT\r\n"
    "\tAkNBMS0wKwYJKoZIhvcNAQkBFh5jYS1vcGVyYXRvckBncmlkLXN1cHBvcnQuYWMu\r\n"
    "\tdWswHhcNMDYwNzI3MTQxMzI4WhcNMDcwNzI3MTQxMzI4WjBbMQswCQYDVQQGEwJV\r\n"
    "\tSzERMA8GA1UEChMIZVNjaWVuY2UxEzARBgNVBAsTCk1hbmNoZXN0ZXIxCzAJBgNV\r\n"
    "\tBAcTmrsogriqMWLAk1DMRcwFQYDVQQDEw5taWNoYWVsIHBhcmQYJKoZIhvcNAQEB\r\n"
    "\tBQADggEPADCCAQoCggEBANPEQBgl1IaKdSS1TbhF3hEXSl72G9J+WC/1R64fAcEF\r\n"
    "\tW51rEyFYiIeZGx/BVzwXbeBoNUK41OK65sxGuflMo5gLflbwJtHBRIEKAfVVp3YR\r\n"
    "\tgW7cMA/s/XKgL1GEC7rQw8lIZT8RApukCGqOVHSi/F1SiFlPDxuDfmdiNzL31+sL\r\n"
    "\t0iwHDdNkGjy5pyBSB8Y79dsSJtCW/iaLB0/n8Sj7HgvvZJ7x0fr+RQjYOUUfrePP\r\n"
    "\tu2MSpFyf+9BbC/aXgaZuiCvSR+8Snv3xApQY+fULK/xY8h8Ua51iXoQ5jrgu2SqR\r\n"
    "\twgA7BUi3G8LFzMBl8FRCDYGUDy7M6QaHXx1ZWIPWNKsCAwEAAaOCAiQwggIgMAwG\r\n"
    "\tA1UdEwEB/wQCMAAwEQYJYIZIAYb4QgHTTPAQDAgWgMA4GA1UdDwEB/wQEAwID6DAs\r\n"
    "\tBglghkgBhvhCAQ0EHxYdVUsgZS1TY2llbmNlIFVzZXIgQ2VydGlmaWNhdGUwHQYD\r\n"
    "\tVR0OBBYEFDTt/sf9PeMaZDHkUIldrDYMNTBZMIGaBgNVHSMEgZIwgY+AFAI4qxGj\r\n"
    "\tloCLDdMVKwiljjDastqooXSkcjBwMQswCQYDVQQGEwJVSzERMA8GA1UEChMIZVNj\r\n"
    "\taWVuY2UxEjAQBgNVBAsTCUF1dGhvcml0eTELMAkGA1UEAxMCQ0ExLTArBgkqhkiG\r\n"
    "\t9w0BCQEWHmNhLW9wZXJhdG9yQGdyaWQtc3VwcG9ydC5hYy51a4IBADApBgNVHRIE\r\n"
    "\tIjAggR5jYS1vcGVyYXRvckBncmlkLXN1cHBvcnQuYWMudWswGQYDVR0gBBIwEDAO\r\n"
    "\tBgwrBgEEAdkvAQEBAQYwPQYJYIZIAYb4QgEEBDAWLmh0dHA6Ly9jYS5ncmlkLXN1\r\n"
    "\tcHBvcnQuYWMudmT4sopwqlBWsvcHViL2NybC9jYWNybC5jcmwwPQYJYIZIAYb4QgEDBDAWLmh0\r\n"
    "\tdHA6Ly9jYS5ncmlkLXN1cHBvcnQuYWMudWsvcHViL2NybC9jYWNybC5jcmwwPwYD\r\n"
    "\tVR0fBDgwNjA0oDKgMIYuaHR0cDovL2NhLmdyaWQt5hYy51ay9wdWIv\r\n"
    "\tY3JsL2NhY3JsLmNybDANBgkqhkiG9w0BAQUFAAOCAQEAS/U4iiooBENGW/Hwmmd3\r\n"
    "\tXCy6Zrt08YjKCzGNjorT98g8uGsqYjSxv/hmi0qlnlHs+k/3Iobc3LjS5AMYr5L8\r\n"
    "\tUO7OSkgFFlLHQyC9JzPfmLCAugvzEbyv4Olnsr8hbxF1MbKZoQxUZtMVu29wjfXk\r\n"
    "\thTeApBv7eaKCWpSp7MCbvgzm74izKhu3vlDk9w6qVrxePfGgpKPqfHiOoGhFnbTK\r\n"
    "\twTC6o2xq5y0qZ03JonF7OJspEd3I5zKY3E+ov7/ZhW6DqT8UFvsAdjvQbXyhV8Eu\r\n"
    "\tYhixw1aKEPzNjNowuIseVogKOLXxWI5vAi5HgXdS0/ES5gDGsABo4fqovUKlgop3\r\n"
    "\tRA==\r\n"
    "\t-----END CERTIFICATE-----\r\n"
    "\r\n";
  test_simple(dumbluck2, HPE_OK);

  const char *corrupted_connection =
    "GET / HTTP/1.1\r\n"
    "Host: www.example.com\r\n"
    "Connection\r\033\065\325eep-Alive\r\n"
    "Accept-Encoding: gzip\r\n"
    "\r\n";
  test_simple(corrupted_connection, HPE_INVALID_HEADER_TOKEN);

  const char *corrupted_header_name =
    "GET / HTTP/1.1\r\n"
    "Host: www.example.com\r\n"
    "X-Some-Header\r\033\065\325eep-Alive\r\n"
    "Accept-Encoding: gzip\r\n"
    "\r\n";
  test_simple(corrupted_header_name, HPE_INVALID_HEADER_TOKEN);

#if 0
  // NOTE(Wed Nov 18 11:57:27 CET 2009) this seems okay. we just read body
  // until EOF.
  //
  // no content-length
  // error if there is a body without content length
  const char *bad_get_no_headers_no_body = "GET /bad_get_no_headers_no_body/world HTTP/1.1\r\n"
                                           "Accept: */*\r\n"
                                           "\r\n"
                                           "HELLO";
  test_simple(bad_get_no_headers_no_body, 0);
#endif
  /* TODO sending junk and large headers gets rejected */


  /* check to make sure our predefined requests are okay */
  for (i = 0; i < ARRAY_SIZE(requests); i++) {
    test_message(&requests[i]);
  }

  for (i = 0; i < ARRAY_SIZE(requests); i++) {
    test_message_pause(&requests[i]);
  }

  for (i = 0; i < ARRAY_SIZE(requests); i++) {
    if (!requests[i].should_keep_alive) continue;
    for (j = 0; j < ARRAY_SIZE(requests); j++) {
      if (!requests[j].should_keep_alive) continue;
      for (k = 0; k < ARRAY_SIZE(requests); k++) {
        test_multiple3(&requests[i], &requests[j], &requests[k]);
      }
    }
  }

  printf("request scan 1/4      ");
  test_scan( &requests[GET_NO_HEADERS_NO_BODY]
           , &requests[GET_ONE_HEADER_NO_BODY]
           , &requests[GET_NO_HEADERS_NO_BODY]
           );

  printf("request scan 2/4      ");
  test_scan( &requests[POST_CHUNKED_ALL_YOUR_BASE]
           , &requests[POST_IDENTITY_BODY_WORLD]
           , &requests[GET_FUNKY_CONTENT_LENGTH]
           );

  printf("request scan 3/4      ");
  test_scan( &requests[TWO_CHUNKS_MULT_ZERO_END]
           , &requests[CHUNKED_W_TRAILING_HEADERS]
           , &requests[CHUNKED_W_NONSENSE_AFTER_LENGTH]
           );

  printf("request scan 4/4      ");
  test_scan( &requests[QUERY_URL_WITH_QUESTION_MARK_GET]
           , &requests[PREFIX_NEWLINE_GET ]
           , &requests[CONNECT_REQUEST]
           );

  puts("requests okay");

  return 0;
}