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
struct TYPE_4__ {char* data; scalar_t__ len; scalar_t__ blocksize; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strlen (char*) ; 

svn_stringbuf_t *
svn_stringbuf_create_wrap(char *str, apr_pool_t *pool)
{
  svn_stringbuf_t *result = apr_palloc(pool, sizeof(*result));
  result->pool = pool;
  result->data = str;
  result->len = strlen(str);
  result->blocksize = result->len + 1;

  return result;
}