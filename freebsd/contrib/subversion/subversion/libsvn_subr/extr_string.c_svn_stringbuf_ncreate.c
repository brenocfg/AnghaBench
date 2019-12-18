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
struct TYPE_4__ {char* data; int len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 

svn_stringbuf_t *
svn_stringbuf_ncreate(const char *bytes, apr_size_t size, apr_pool_t *pool)
{
  svn_stringbuf_t *strbuf = svn_stringbuf_create_ensure(size, pool);

  /* If SIZE is 0, NULL is valid for BYTES. */
  if (size)
    memcpy(strbuf->data, bytes, size);

  /* Null termination is the convention -- even if we suspect the data
     to be binary, it's not up to us to decide, it's the caller's
     call.  Heck, that's why they call it the caller! */
  strbuf->data[size] = '\0';
  strbuf->len = size;

  return strbuf;
}