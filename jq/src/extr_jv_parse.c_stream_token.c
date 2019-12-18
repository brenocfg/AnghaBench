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
struct jv_parser {void* last_seen; int /*<<< orphan*/  stacklen; void* path; void* output; void* next; } ;
typedef  char* pfunc ;
typedef  int /*<<< orphan*/  jv_kind ;
typedef  void* jv ;

/* Variables and functions */
 void* JV_ARRAY (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  JV_KIND_NULL ; 
 int /*<<< orphan*/  JV_KIND_NUMBER ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 void* JV_LAST_COLON ; 
 void* JV_LAST_COMMA ; 
 void* JV_LAST_NONE ; 
 void* JV_LAST_OPEN_ARRAY ; 
 void* JV_LAST_OPEN_OBJECT ; 
 void* JV_LAST_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* jv_array () ; 
 void* jv_array_append (void*,void*) ; 
 void* jv_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* jv_array_set (void*,int /*<<< orphan*/ ,void*) ; 
 void* jv_array_slice (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (void*) ; 
 int /*<<< orphan*/  jv_free (void*) ; 
 int /*<<< orphan*/  jv_get_kind (void*) ; 
 void* jv_invalid () ; 
 int /*<<< orphan*/  jv_is_valid (void*) ; 
 void* jv_null () ; 
 void* jv_number (int) ; 
 int jv_number_value (void*) ; 
 void* jv_object () ; 
 void* jv_true () ; 

__attribute__((used)) static pfunc stream_token(struct jv_parser* p, char ch) {
  jv_kind k;
  jv last;

  switch (ch) {
  case '[':
    if (jv_is_valid(p->next))
      return "Expected a separator between values";
    p->path = jv_array_append(p->path, jv_number(0)); // push
    p->last_seen = JV_LAST_OPEN_ARRAY;
    p->stacklen++;
    break;

  case '{':
    if (p->last_seen == JV_LAST_VALUE)
      return "Expected a separator between values";
    // Push object key: null, since we don't know it yet
    p->path = jv_array_append(p->path, jv_null()); // push
    p->last_seen = JV_LAST_OPEN_OBJECT;
    p->stacklen++;
    break;

  case ':':
    last = jv_invalid();
    if (p->stacklen == 0 || jv_get_kind(last = jv_array_get(jv_copy(p->path), p->stacklen - 1)) == JV_KIND_NUMBER) {
      jv_free(last);
      return "':' not as part of an object";
    }
    jv_free(last);
    if (!jv_is_valid(p->next) || p->last_seen == JV_LAST_NONE)
      return "Expected string key before ':'";
    if (jv_get_kind(p->next) != JV_KIND_STRING)
      return "Object keys must be strings";
    if (p->last_seen != JV_LAST_VALUE)
      return "':' should follow a key";
    p->last_seen = JV_LAST_COLON;
    p->path = jv_array_set(p->path, p->stacklen - 1, p->next);
    p->next = jv_invalid();
    break;

  case ',':
    if (p->last_seen != JV_LAST_VALUE)
      return "Expected value before ','";
    if (p->stacklen == 0)
      return "',' not as part of an object or array";
    last = jv_array_get(jv_copy(p->path), p->stacklen - 1);
    k = jv_get_kind(last);
    if (k == JV_KIND_NUMBER) {
      int idx = jv_number_value(last);

      if (jv_is_valid(p->next)) {
        p->output = JV_ARRAY(jv_copy(p->path), p->next);
        p->next = jv_invalid();
      }
      p->path = jv_array_set(p->path, p->stacklen - 1, jv_number(idx + 1));
      p->last_seen = JV_LAST_COMMA;
    } else if (k == JV_KIND_STRING) {
      if (jv_is_valid(p->next)) {
        p->output = JV_ARRAY(jv_copy(p->path), p->next);
        p->next = jv_invalid();
      }
      p->path = jv_array_set(p->path, p->stacklen - 1, jv_true()); // ready for another name:value pair
      p->last_seen = JV_LAST_COMMA;
    } else {
      assert(k == JV_KIND_NULL);
      // this case hits on input like {,}
      // make sure to handle input like {"a", "b"} and {"a":, ...}
      jv_free(last);
      return "Objects must consist of key:value pairs";
    }
    jv_free(last);
    break;

  case ']':
    if (p->stacklen == 0)
      return "Unmatched ']' at the top-level";
    if (p->last_seen == JV_LAST_COMMA)
      return "Expected another array element";
    if (p->last_seen == JV_LAST_OPEN_ARRAY)
      assert(!jv_is_valid(p->next));

    last = jv_array_get(jv_copy(p->path), p->stacklen - 1);
    k = jv_get_kind(last);
    jv_free(last);

    if (k != JV_KIND_NUMBER)
      return "Unmatched ']' in the middle of an object";
    if (jv_is_valid(p->next)) {
      p->output = JV_ARRAY(jv_copy(p->path), p->next, jv_true());
      p->next = jv_invalid();
    } else if (p->last_seen != JV_LAST_OPEN_ARRAY) {
      p->output = JV_ARRAY(jv_copy(p->path));
    }

    p->path = jv_array_slice(p->path, 0, --(p->stacklen)); // pop
    //assert(!jv_is_valid(p->next));
    jv_free(p->next);
    p->next = jv_invalid();

    if (p->last_seen == JV_LAST_OPEN_ARRAY)
      p->output = JV_ARRAY(jv_copy(p->path), jv_array()); // Empty arrays are leaves

    if (p->stacklen == 0)
      p->last_seen = JV_LAST_NONE;
    else
      p->last_seen = JV_LAST_VALUE;
    break;

  case '}':
    if (p->stacklen == 0)
      return "Unmatched '}' at the top-level";
    if (p->last_seen == JV_LAST_COMMA)
      return "Expected another key:value pair";
    if (p->last_seen == JV_LAST_OPEN_OBJECT)
      assert(!jv_is_valid(p->next));

    last = jv_array_get(jv_copy(p->path), p->stacklen - 1);
    k = jv_get_kind(last);
    jv_free(last);
    if (k == JV_KIND_NUMBER)
      return "Unmatched '}' in the middle of an array";

    if (jv_is_valid(p->next)) {
      if (k != JV_KIND_STRING)
        return "Objects must consist of key:value pairs";
      p->output = JV_ARRAY(jv_copy(p->path), p->next, jv_true());
      p->next = jv_invalid();
    } else {
      // Perhaps {"a":[]}
      if (p->last_seen == JV_LAST_COLON)
        // Looks like {"a":}
        return "Missing value in key:value pair";
      if (p->last_seen == JV_LAST_COMMA)
        // Looks like {"a":0,}
        return "Expected another key-value pair";
      if (p->last_seen == JV_LAST_OPEN_ARRAY)
        return "Unmatched '}' in the middle of an array";
      if (p->last_seen != JV_LAST_VALUE && p->last_seen != JV_LAST_OPEN_OBJECT)
        return "Unmatched '}'";
      if (p->last_seen != JV_LAST_OPEN_OBJECT)
        p->output = JV_ARRAY(jv_copy(p->path));
    }
    p->path = jv_array_slice(p->path, 0, --(p->stacklen)); // pop
    jv_free(p->next);
    p->next = jv_invalid();

    if (p->last_seen == JV_LAST_OPEN_OBJECT)
      p->output = JV_ARRAY(jv_copy(p->path), jv_object()); // Empty arrays are leaves

    if (p->stacklen == 0)
      p->last_seen = JV_LAST_NONE;
    else
      p->last_seen = JV_LAST_VALUE;
    break;
  }
  return 0;
}