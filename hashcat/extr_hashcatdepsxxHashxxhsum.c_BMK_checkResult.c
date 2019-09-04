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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void BMK_checkResult(U32 r1, U32 r2)
{
    static int nbTests = 1;
    if (r1==r2) {
        DISPLAYLEVEL(3, "\rTest%3i : %08X == %08X   ok   ", nbTests, r1, r2);
    } else {
        DISPLAY("\rERROR : Test%3i : %08X <> %08X   !!!!!   \n", nbTests, r1, r2);
        exit(1);
    }
    nbTests++;
}