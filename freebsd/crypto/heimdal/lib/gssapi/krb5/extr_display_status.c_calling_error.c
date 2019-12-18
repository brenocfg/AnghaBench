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
typedef  int /*<<< orphan*/  msgs ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int GSS_C_CALLING_ERROR_OFFSET ; 

__attribute__((used)) static const char *
calling_error(OM_uint32 v)
{
    static const char *msgs[] = {
	NULL,			/* 0 */
	"A required input parameter could not be read.", /*  */
	"A required output parameter could not be written.", /*  */
	"A parameter was malformed"
    };

    v >>= GSS_C_CALLING_ERROR_OFFSET;

    if (v == 0)
	return "";
    else if (v >= sizeof(msgs)/sizeof(*msgs))
	return "unknown calling error";
    else
	return msgs[v];
}