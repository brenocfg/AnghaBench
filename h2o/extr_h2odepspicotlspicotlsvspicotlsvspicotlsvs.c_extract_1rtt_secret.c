#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptls_t ;
struct TYPE_6__ {TYPE_1__* hash; } ;
typedef  TYPE_2__ ptls_cipher_suite_t ;
struct TYPE_5__ {size_t digest_size; } ;

/* Variables and functions */
 int ptls_export_secret (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,char const*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ptls_get_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int extract_1rtt_secret( 
    ptls_t *tls, const char *label, 
    ptls_cipher_suite_t ** cipher,
    uint8_t * secret, size_t secret_max)
{
    int ret = 0;
    *cipher = ptls_get_cipher(tls);

    if (*cipher == NULL)
    {
        ret = -1;
    }
    else if ((*cipher)->hash->digest_size > secret_max)
    {
        ret = -1;
    }
    else
    {
        ret = ptls_export_secret(tls, secret, (*cipher)->hash->digest_size,
            label, ptls_iovec_init(NULL, 0), 1);
    }

    return 0;
}