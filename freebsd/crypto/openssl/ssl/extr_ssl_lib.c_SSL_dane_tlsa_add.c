#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  dane; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int dane_tlsa_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int SSL_dane_tlsa_add(SSL *s, uint8_t usage, uint8_t selector,
                      uint8_t mtype, unsigned const char *data, size_t dlen)
{
    return dane_tlsa_add(&s->dane, usage, selector, mtype, data, dlen);
}