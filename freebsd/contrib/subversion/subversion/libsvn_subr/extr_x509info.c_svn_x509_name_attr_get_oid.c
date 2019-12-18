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
struct TYPE_3__ {unsigned char const* oid; int /*<<< orphan*/  oid_len; } ;
typedef  TYPE_1__ svn_x509_name_attr_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */

const unsigned char *
svn_x509_name_attr_get_oid(const svn_x509_name_attr_t *attr, apr_size_t *len)
{
  *len = attr->oid_len;
  return attr->oid;
}