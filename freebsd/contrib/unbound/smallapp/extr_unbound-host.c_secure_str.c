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
struct ub_result {int rcode; scalar_t__ bogus; scalar_t__ secure; } ;

/* Variables and functions */

__attribute__((used)) static const char* 
secure_str(struct ub_result* result)
{
	if(result->rcode != 0 && result->rcode != 3) return "(error)";
	if(result->secure) return "(secure)";
	if(result->bogus) return "(BOGUS (security failure))";
	return "(insecure)";
}