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
typedef  int /*<<< orphan*/  value ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ svn_membuf_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_membuf__resize (TYPE_1__*,int) ; 

__attribute__((used)) static void
membuf_insert_ucs4(svn_membuf_t *buf, apr_size_t offset, apr_int32_t value)
{
  svn_membuf__resize(buf, (offset + 1) * sizeof(value));
  ((apr_int32_t*)buf->data)[offset] = value;
}