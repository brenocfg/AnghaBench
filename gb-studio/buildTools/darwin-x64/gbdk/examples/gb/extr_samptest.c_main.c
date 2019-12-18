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
 int /*<<< orphan*/  J_START ; 
 int SAMPLES ; 
 int /*<<< orphan*/  play_sample (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  sample ; 
 int /*<<< orphan*/  waitpad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpadup () ; 

void main()
{
	puts("\n    Ren & Stimpy\n");
	while(1)
	{
		waitpad(J_START);
		puts(".");
		play_sample(sample, SAMPLES / 32);
		waitpadup();
	}
}