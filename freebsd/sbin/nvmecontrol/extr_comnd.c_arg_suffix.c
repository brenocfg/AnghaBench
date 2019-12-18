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
typedef  int arg_type ;

/* Variables and functions */
#define  arg_none 130 
#define  arg_path 129 
#define  arg_string 128 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static void
arg_suffix(char *buf, size_t len, arg_type at)
{
	switch (at) {
	case arg_none:
		break;
	case arg_string:
		strlcat(buf, "=<STRING>", len);
		break;
	case arg_path:
		strlcat(buf, "=<FILE>", len);
		break;
	default:
		strlcat(buf, "=<NUM>", len);
		break;
	}
}