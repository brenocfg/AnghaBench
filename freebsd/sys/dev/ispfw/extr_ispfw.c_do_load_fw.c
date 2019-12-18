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
 int /*<<< orphan*/  RMACRO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_1000 ; 
 int /*<<< orphan*/  isp_1040 ; 
 int /*<<< orphan*/  isp_1080 ; 
 int /*<<< orphan*/  isp_12160 ; 
 int /*<<< orphan*/  isp_2100 ; 
 int /*<<< orphan*/  isp_2200 ; 
 int /*<<< orphan*/  isp_2300 ; 
 int /*<<< orphan*/  isp_2322 ; 
 int /*<<< orphan*/  isp_2400 ; 
 int /*<<< orphan*/  isp_2500 ; 

__attribute__((used)) static int
do_load_fw(void)
{

#if	defined(ISP_1000)
	RMACRO(isp_1000);
#endif
#if	defined(ISP_1040)
	RMACRO(isp_1040);
#endif
#if	defined(ISP_1080)
	RMACRO(isp_1080);
#endif
#if	defined(ISP_12160)
	RMACRO(isp_12160);
#endif
#if	defined(ISP_2100)
	RMACRO(isp_2100);
#endif
#if	defined(ISP_2200)
	RMACRO(isp_2200);
#endif
#if	defined(ISP_2300)
	RMACRO(isp_2300);
#endif
#if	defined(ISP_2322)
	RMACRO(isp_2322);
#endif
#if	defined(ISP_2400)
	RMACRO(isp_2400);
#endif
#if	defined(ISP_2500)
	RMACRO(isp_2500);
#endif
	return (0);
}