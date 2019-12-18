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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  uri_autoescape_chars ; 
 char const* uri_escape (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_path_uri_autoescape(const char *uri, apr_pool_t *pool)
{
  return uri_escape(uri, uri_autoescape_chars, pool);
}