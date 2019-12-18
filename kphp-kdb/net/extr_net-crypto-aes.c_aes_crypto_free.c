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
struct connection {scalar_t__ crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_aes_crypto ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

int aes_crypto_free (struct connection *c) {
  if (c->crypto) {
    free (c->crypto);
    c->crypto = 0;
    --allocated_aes_crypto;
  }
  return 0;
}