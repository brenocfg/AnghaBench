#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_uri_is_canonical (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ uri_schema_root_length (char const*,scalar_t__) ; 

svn_boolean_t
svn_uri_is_root(const char *uri, apr_size_t len)
{
  assert(svn_uri_is_canonical(uri, NULL));
  return (len == uri_schema_root_length(uri, len));
}