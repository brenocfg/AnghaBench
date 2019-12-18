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
typedef  enum http_errno { ____Placeholder_http_errno } http_errno ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_REQUEST ; 
 int /*<<< orphan*/  test_simple_type (char const*,int,int /*<<< orphan*/ ) ; 

void
test_simple (const char *buf, enum http_errno err_expected)
{
  test_simple_type(buf, err_expected, HTTP_REQUEST);
}