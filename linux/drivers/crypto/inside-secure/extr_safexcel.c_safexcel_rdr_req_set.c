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
struct safexcel_result_desc {int dummy; } ;
struct safexcel_crypto_priv {TYPE_1__* ring; } ;
struct crypto_async_request {int dummy; } ;
struct TYPE_2__ {struct crypto_async_request** rdr_req; } ;

/* Variables and functions */
 int safexcel_ring_rdr_rdesc_index (struct safexcel_crypto_priv*,int,struct safexcel_result_desc*) ; 

inline void safexcel_rdr_req_set(struct safexcel_crypto_priv *priv,
				 int ring,
				 struct safexcel_result_desc *rdesc,
				 struct crypto_async_request *req)
{
	int i = safexcel_ring_rdr_rdesc_index(priv, ring, rdesc);

	priv->ring[ring].rdr_req[i] = req;
}