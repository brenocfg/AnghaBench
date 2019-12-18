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
typedef  int /*<<< orphan*/  u_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  V_pf_tags ; 
 int /*<<< orphan*/  tagname2tag (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static u_int16_t
pf_tagname2tag(char *tagname)
{
	return (tagname2tag(&V_pf_tags, tagname));
}