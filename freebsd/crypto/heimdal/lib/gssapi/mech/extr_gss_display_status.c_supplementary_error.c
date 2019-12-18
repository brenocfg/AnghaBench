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
 int GSS_C_SUPPLEMENTARY_OFFSET ; 

__attribute__((used)) static const char *
supplementary_error(OM_uint32 v)
{
    static const char *msgs[] = {
	"normal completion",
	"continuation call to routine required",
	"duplicate per-message token detected",
	"timed-out per-message token detected",
	"reordered (early) per-message token detected",
	"skipped predecessor token(s) detected"
    };

    v >>= GSS_C_SUPPLEMENTARY_OFFSET;

    if (v >= sizeof(msgs)/sizeof(*msgs))
	return "unknown routine error";
    else
	return msgs[v];
}