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
struct aldap {int err; } ;

/* Variables and functions */
#define  ALDAP_ERR_INVALID_FILTER 131 
#define  ALDAP_ERR_OPERATION_FAILED 130 
#define  ALDAP_ERR_PARSER_ERROR 129 
#define  ALDAP_ERR_SUCCESS 128 

int
aldap_get_errno(struct aldap *a, const char **estr)
{
	switch (a->err) {
	case ALDAP_ERR_SUCCESS:
		*estr = "success";
		break;
	case ALDAP_ERR_PARSER_ERROR:
		*estr = "parser failed";
		break;
	case ALDAP_ERR_INVALID_FILTER:
		*estr = "invalid filter";
		break;
	case ALDAP_ERR_OPERATION_FAILED:
		*estr = "operation failed";
		break;
	default:
		*estr = "unknown";
		break;
	}
	return (a->err);
}