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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int ssl_print_text (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ssl_print_vmsg(RES* ssl, const char* format, va_list args)
{
	char msg[1024];
	vsnprintf(msg, sizeof(msg), format, args);
	return ssl_print_text(ssl, msg);
}