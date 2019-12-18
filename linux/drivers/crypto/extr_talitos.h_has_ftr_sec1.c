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
struct talitos_private {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRYPTO_DEV_TALITOS1 ; 
 int /*<<< orphan*/  CONFIG_CRYPTO_DEV_TALITOS2 ; 
 int IS_ENABLED (int /*<<< orphan*/ ) ; 
 int TALITOS_FTR_SEC1 ; 

__attribute__((used)) static inline bool has_ftr_sec1(struct talitos_private *priv)
{
	if (IS_ENABLED(CONFIG_CRYPTO_DEV_TALITOS1) &&
	    IS_ENABLED(CONFIG_CRYPTO_DEV_TALITOS2))
		return priv->features & TALITOS_FTR_SEC1;

	return IS_ENABLED(CONFIG_CRYPTO_DEV_TALITOS1);
}