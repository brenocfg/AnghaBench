#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  md; int /*<<< orphan*/  cipher; } ;
struct TYPE_6__ {TYPE_1__ generating; } ;
struct TYPE_7__ {TYPE_2__ vars; int /*<<< orphan*/  update_thread; } ;
struct TYPE_8__ {TYPE_3__ ticket; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  ticket_internal_updater ; 

__attribute__((used)) static void ticket_init_defaults(void)
{
    conf.ticket.update_thread = ticket_internal_updater;
    /* to protect the secret >>>2030 we need AES-256 (http://www.keylength.com/en/4/) */
    conf.ticket.vars.generating.cipher = EVP_aes_256_cbc();
    /* integrity checks are only necessary at the time of handshake, and sha256 (recommended by RFC 5077) is sufficient */
    conf.ticket.vars.generating.md = EVP_sha256();
}