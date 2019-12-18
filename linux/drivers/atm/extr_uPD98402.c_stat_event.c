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
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_LIMITED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B1ECT ; 
 int /*<<< orphan*/  B2ECT ; 
 int /*<<< orphan*/  B3ECT ; 
 unsigned char GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LECCT ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  PFECB ; 
 int /*<<< orphan*/  line_bip ; 
 int /*<<< orphan*/  line_febe ; 
 int /*<<< orphan*/  path_bip ; 
 int /*<<< orphan*/  path_febe ; 
 int /*<<< orphan*/  section_bip ; 
 unsigned char uPD98402_PFM_B1E ; 
 unsigned char uPD98402_PFM_B2E ; 
 unsigned char uPD98402_PFM_B3E ; 
 unsigned char uPD98402_PFM_LFEB ; 
 unsigned char uPD98402_PFM_PFEB ; 

__attribute__((used)) static void stat_event(struct atm_dev *dev)
{
	unsigned char events;

	events = GET(PCR);
	if (events & uPD98402_PFM_PFEB) ADD_LIMITED(path_febe,PFECB);
	if (events & uPD98402_PFM_LFEB) ADD_LIMITED(line_febe,LECCT);
	if (events & uPD98402_PFM_B3E) ADD_LIMITED(path_bip,B3ECT);
	if (events & uPD98402_PFM_B2E) ADD_LIMITED(line_bip,B2ECT);
	if (events & uPD98402_PFM_B1E) ADD_LIMITED(section_bip,B1ECT);
}