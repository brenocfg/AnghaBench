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
struct ht16k33_fbdev {int refresh_rate; int /*<<< orphan*/  work; } ;
struct ht16k33_priv {struct ht16k33_fbdev fbdev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ht16k33_fb_queue(struct ht16k33_priv *priv)
{
	struct ht16k33_fbdev *fbdev = &priv->fbdev;

	schedule_delayed_work(&fbdev->work,
			      msecs_to_jiffies(HZ / fbdev->refresh_rate));
}