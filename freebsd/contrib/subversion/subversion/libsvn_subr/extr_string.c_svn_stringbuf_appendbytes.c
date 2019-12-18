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
struct TYPE_4__ {int len; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,int) ; 

void
svn_stringbuf_appendbytes(svn_stringbuf_t *str, const char *bytes,
                          apr_size_t count)
{
  apr_size_t total_len;
  void *start_address;

  if (!count)
    /* Allow BYTES to be NULL by avoiding passing it to memcpy. */
    return;

  total_len = str->len + count;  /* total size needed */

  /* svn_stringbuf_ensure adds 1 for null terminator. */
  svn_stringbuf_ensure(str, total_len);

  /* get address 1 byte beyond end of original bytestring */
  start_address = (str->data + str->len);

  memcpy(start_address, bytes, count);
  str->len = total_len;

  str->data[str->len] = '\0';  /* We don't know if this is binary
                                  data or not, but convention is
                                  to null-terminate. */
}