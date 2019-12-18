#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {char* data; int length_hashed; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_2__ jvp_string ;
struct TYPE_6__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_8__ {TYPE_1__ member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_FLAGS_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* jvp_string_alloc (int) ; 
 int /*<<< orphan*/  jvp_utf8_encode (int,char*) ; 
 char* jvp_utf8_next (char const*,char const*,int*) ; 

__attribute__((used)) static jv jvp_string_copy_replace_bad(const char* data, uint32_t length) {
  const char* end = data + length;
  const char* i = data;
  const char* cstart;

  uint32_t maxlength = length * 3 + 1; // worst case: all bad bytes, each becomes a 3-byte U+FFFD
  jvp_string* s = jvp_string_alloc(maxlength);
  char* out = s->data;
  int c = 0;

  while ((i = jvp_utf8_next((cstart = i), end, &c))) {
    if (c == -1) {
      c = 0xFFFD; // U+FFFD REPLACEMENT CHARACTER
    }
    out += jvp_utf8_encode(c, out);
    assert(out < s->data + maxlength);
  }
  length = out - s->data;
  s->data[length] = 0;
  s->length_hashed = length << 1;
  jv r = {JVP_FLAGS_STRING, 0, 0, 0, {&s->refcnt}};
  return r;
}