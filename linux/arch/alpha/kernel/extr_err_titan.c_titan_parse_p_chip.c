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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int titan_parse_p_agperror (int,int /*<<< orphan*/ ,int) ; 
 int titan_parse_p_perror (int,int,int /*<<< orphan*/ ,int) ; 
 int titan_parse_p_serror (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
titan_parse_p_chip(int which, u64 serror, u64 gperror, 
		   u64 aperror, u64 agperror, int print)
{
	int status = MCHK_DISPOSITION_UNKNOWN_ERROR;
	status |= titan_parse_p_serror(which, serror, print);
	status |= titan_parse_p_perror(which, 0, gperror, print);
	status |= titan_parse_p_perror(which, 1, aperror, print);
	status |= titan_parse_p_agperror(which, agperror, print);
	return status;
}