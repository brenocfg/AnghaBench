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
struct safexcel_crypto_priv {TYPE_1__* ring; } ;
struct crypto_async_request {int dummy; } ;
struct TYPE_2__ {struct crypto_async_request** rdr_req; } ;

/* Variables and functions */
 int safexcel_ring_first_rdr_index (struct safexcel_crypto_priv*,int) ; 

inline struct crypto_async_request *
safexcel_rdr_req_get(struct safexcel_crypto_priv *priv, int ring)
{
	int i = safexcel_ring_first_rdr_index(priv, ring);

	return priv->ring[ring].rdr_req[i];
}