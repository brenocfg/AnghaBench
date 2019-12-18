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
struct ipoib_path {int dummy; } ;
struct ipoib_dev_priv {int dummy; } ;
struct ipoib_cm_tx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct ipoib_cm_tx *ipoib_cm_create_tx(struct ipoib_dev_priv *priv, struct ipoib_path *path)
{
	return NULL;
}