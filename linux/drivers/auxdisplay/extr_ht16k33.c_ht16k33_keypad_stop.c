#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int dummy; } ;
struct ht16k33_keypad {int stopped; TYPE_1__* client; int /*<<< orphan*/  wait; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct ht16k33_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ht16k33_keypad_stop(struct input_dev *dev)
{
	struct ht16k33_keypad *keypad = input_get_drvdata(dev);

	keypad->stopped = true;
	mb();
	wake_up(&keypad->wait);
	disable_irq(keypad->client->irq);
}