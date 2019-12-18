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

/* Variables and functions */
#define  ERRSET_FAIL 133 
#define  ERRSET_INVAL 132 
#define  ERRSET_NODATA 131 
#define  ERRSET_NOMEMORY 130 
#define  ERRSET_NONAME 129 
#define  ERRSET_SUCCESS 128 
 char const** errset_text ; 

__attribute__((used)) static const char *
dns_result_totext(unsigned int res)
{
	switch (res) {
	case ERRSET_SUCCESS:
		return errset_text[ERRSET_SUCCESS];
	case ERRSET_NOMEMORY:
		return errset_text[ERRSET_NOMEMORY];
	case ERRSET_FAIL:
		return errset_text[ERRSET_FAIL];
	case ERRSET_INVAL:
		return errset_text[ERRSET_INVAL];
	case ERRSET_NONAME:
		return errset_text[ERRSET_NONAME];
	case ERRSET_NODATA:
		return errset_text[ERRSET_NODATA];
	default:
		return "unknown error";
	}
}