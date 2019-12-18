#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  decode_bytes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

svn_stringbuf_t *
svn_quoprint_decode_string(const svn_stringbuf_t *str, apr_pool_t *pool)
{
  svn_stringbuf_t *decoded = svn_stringbuf_create_empty(pool);
  char ingroup[4];
  int ingrouplen = 0;

  decode_bytes(decoded, str->data, str->len, ingroup, &ingrouplen);
  return decoded;
}