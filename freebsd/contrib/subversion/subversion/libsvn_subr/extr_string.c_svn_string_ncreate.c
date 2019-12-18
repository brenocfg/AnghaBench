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
typedef  TYPE_1__ svn_string_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

svn_string_t *
svn_string_ncreate(const char *bytes, apr_size_t size, apr_pool_t *pool)
{
  void *mem;
  char *data;
  svn_string_t *new_string;

  /* Allocate memory for svn_string_t and data in one chunk. */
  mem = apr_palloc(pool, sizeof(*new_string) + size + 1);
  data = (char*)mem + sizeof(*new_string);

  new_string = mem;
  new_string->data = data;
  new_string->len = size;

  /* If SIZE is 0, NULL is valid for BYTES. */
  if (size)
    memcpy(data, bytes, size);

  /* Null termination is the convention -- even if we suspect the data
     to be binary, it's not up to us to decide, it's the caller's
     call.  Heck, that's why they call it the caller! */
  data[size] = '\0';

  return new_string;
}