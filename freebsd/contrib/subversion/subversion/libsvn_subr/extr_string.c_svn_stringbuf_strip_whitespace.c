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
struct TYPE_3__ {char* data; int len; int /*<<< orphan*/  blocksize; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ string_first_non_whitespace (char*,int) ; 
 scalar_t__ svn_ctype_isspace (char) ; 

void
svn_stringbuf_strip_whitespace(svn_stringbuf_t *str)
{
  /* Skip (hide) whitespace at the beginning of the string. */
  if (svn_ctype_isspace(str->data[0]))
    {
      /* Find first non-whitespace character */
      apr_size_t offset = string_first_non_whitespace(str->data + 1,
                                                      str->len - 1) + 1;

      /* Go ahead!  Waste some RAM, we've got pools! :)  */
      str->data += offset;
      str->len -= offset;
      str->blocksize -= offset;
    }

  /* Now that we've trimmed the front, trim the end, wasting more RAM. */
  while ((str->len > 0) && svn_ctype_isspace(str->data[str->len - 1]))
    str->len--;
  str->data[str->len] = '\0';
}