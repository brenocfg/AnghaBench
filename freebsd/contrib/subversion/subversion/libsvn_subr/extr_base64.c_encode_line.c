#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; int len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;

/* Variables and functions */
 int BASE64_LINELEN ; 
 int /*<<< orphan*/  encode_group (unsigned char const*,char*) ; 

__attribute__((used)) static void
encode_line(svn_stringbuf_t *str, const char *data)
{
  /* Translate directly from DATA to STR->DATA. */
  const unsigned char *in = (const unsigned char *)data;
  char *out = str->data + str->len;
  char *end = out + BASE64_LINELEN;

  /* We assume that BYTES_PER_LINE is a multiple of 3 and BASE64_LINELEN
     a multiple of 4. */
  for ( ; out != end; in += 3, out += 4)
    encode_group(in, out);

  /* Expand and terminate the string. */
  *out = '\0';
  str->len += BASE64_LINELEN;
}