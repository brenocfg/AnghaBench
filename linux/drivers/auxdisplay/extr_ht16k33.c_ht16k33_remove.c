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
struct i2c_client {int dummy; } ;
struct ht16k33_fbdev {scalar_t__ buffer; int /*<<< orphan*/  info; int /*<<< orphan*/  work; } ;
struct ht16k33_priv {struct ht16k33_fbdev fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 struct ht16k33_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ht16k33_remove(struct i2c_client *client)
{
	struct ht16k33_priv *priv = i2c_get_clientdata(client);
	struct ht16k33_fbdev *fbdev = &priv->fbdev;

	cancel_delayed_work_sync(&fbdev->work);
	unregister_framebuffer(fbdev->info);
	framebuffer_release(fbdev->info);
	free_page((unsigned long) fbdev->buffer);

	return 0;
}