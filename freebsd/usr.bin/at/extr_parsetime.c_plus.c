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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMBER ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_or_minus (struct tm*,int) ; 
 int /*<<< orphan*/  sc_token ; 

__attribute__((used)) static void
plus(struct tm *tm)
{
    int delay;

    expect(NUMBER);

    delay = atoi(sc_token);
    plus_or_minus(tm, delay);
}