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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct crb_priv {int dummy; } ;

/* Variables and functions */
 int __crb_request_locality (int /*<<< orphan*/ *,struct crb_priv*,int) ; 
 struct crb_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crb_request_locality(struct tpm_chip *chip, int loc)
{
	struct crb_priv *priv = dev_get_drvdata(&chip->dev);

	return __crb_request_locality(&chip->dev, priv, loc);
}