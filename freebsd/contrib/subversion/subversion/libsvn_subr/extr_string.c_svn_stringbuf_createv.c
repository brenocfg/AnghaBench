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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_4__ {char* data; int /*<<< orphan*/ * pool; void* blocksize; void* len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  void* apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pvsprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 void* strlen (char*) ; 

svn_stringbuf_t *
svn_stringbuf_createv(apr_pool_t *pool, const char *fmt, va_list ap)
{
  char *data = apr_pvsprintf(pool, fmt, ap);
  apr_size_t size = strlen(data);
  svn_stringbuf_t *new_string;

  new_string = apr_palloc(pool, sizeof(*new_string));
  new_string->data = data;
  new_string->len = size;
  new_string->blocksize = size + 1;
  new_string->pool = pool;

  return new_string;
}