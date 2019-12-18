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
struct advert {scalar_t__ price; int /*<<< orphan*/  delta; int /*<<< orphan*/  g_sump2; int /*<<< orphan*/  g_sump1; int /*<<< orphan*/  g_sump0; int /*<<< orphan*/  lambda; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_ad_lambda_delta (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void compute_ad_lambda (struct advert *A) {
  if (A->price <= 0) {
    return;
  }
  A->lambda = compute_ad_lambda_delta (A->price, A->g_sump0, A->g_sump1, A->g_sump2, &A->delta);
}