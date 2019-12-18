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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ UINT16_MAX ; 
 scalar_t__ git__isspace (char const) ; 
 int git__strntol32 (scalar_t__*,char const*,size_t,char const**,int) ; 

__attribute__((used)) static int parse_mode(uint16_t *mode_out, const char *buffer, size_t buffer_len, const char **buffer_out)
{
	int32_t mode;
	int error;

	if (!buffer_len || git__isspace(*buffer))
		return -1;

	if ((error = git__strntol32(&mode, buffer, buffer_len, buffer_out, 8)) < 0)
		return error;

	if (mode < 0 || mode > UINT16_MAX)
		return -1;

	*mode_out = mode;

	return 0;
}