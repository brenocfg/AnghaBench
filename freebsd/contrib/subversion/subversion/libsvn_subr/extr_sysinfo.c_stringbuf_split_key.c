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
struct TYPE_4__ {char* data; int len; int blocksize; } ;
typedef  TYPE_1__ svn_stringbuf_t ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_strip_whitespace (TYPE_1__*) ; 

__attribute__((used)) static const char *
stringbuf_split_key(svn_stringbuf_t *buffer, char delim)
{
  char *key;
  char *end;

  end = strchr(buffer->data, delim);
  if (!end)
    return NULL;

  svn_stringbuf_strip_whitespace(buffer);

  /* Now we split the currently allocated buffer in two parts:
      - a const char * HEAD
      - the remaining stringbuf_t. */

  /* Create HEAD as '\0' terminated const char * */
  key = buffer->data;
  end = strchr(key, delim);
  *end = '\0';

  /* And update the TAIL to be a smaller, but still valid stringbuf */
  buffer->data = end + 1;
  buffer->len -= 1 + end - key;
  buffer->blocksize -= 1 + end - key;

  svn_stringbuf_strip_whitespace(buffer);

  return key;
}