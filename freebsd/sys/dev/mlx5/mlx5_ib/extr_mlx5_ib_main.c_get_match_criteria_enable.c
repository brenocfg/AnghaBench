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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_IS_ZERO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MATCH_CRITERIA_ENABLE_INNER_BIT ; 
 int MATCH_CRITERIA_ENABLE_MISC_BIT ; 
 int MATCH_CRITERIA_ENABLE_OUTER_BIT ; 
 int /*<<< orphan*/  inner_headers ; 
 int /*<<< orphan*/  misc_parameters ; 
 int /*<<< orphan*/  outer_headers ; 

__attribute__((used)) static u8 get_match_criteria_enable(u32 *match_criteria)
{
	u8 match_criteria_enable;

	match_criteria_enable =
		(!HEADER_IS_ZERO(match_criteria, outer_headers)) <<
		MATCH_CRITERIA_ENABLE_OUTER_BIT;
	match_criteria_enable |=
		(!HEADER_IS_ZERO(match_criteria, misc_parameters)) <<
		MATCH_CRITERIA_ENABLE_MISC_BIT;
	match_criteria_enable |=
		(!HEADER_IS_ZERO(match_criteria, inner_headers)) <<
		MATCH_CRITERIA_ENABLE_INNER_BIT;

	return match_criteria_enable;
}