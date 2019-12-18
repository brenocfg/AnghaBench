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
typedef  int /*<<< orphan*/  u8 ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct tpm_atmel_priv {int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct tpm_atmel_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_atml_send(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct tpm_atmel_priv *priv = dev_get_drvdata(&chip->dev);
	int i;

	dev_dbg(&chip->dev, "tpm_atml_send:\n");
	for (i = 0; i < count; i++) {
		dev_dbg(&chip->dev, "%d 0x%x(%d)\n",  i, buf[i], buf[i]);
		iowrite8(buf[i], priv->iobase);
	}

	return 0;
}