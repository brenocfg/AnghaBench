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
struct sec_softc {int dummy; } ;
struct sec_session {int dummy; } ;
struct cryptoini {int /*<<< orphan*/  cri_alg; } ;

/* Variables and functions */
 scalar_t__ sec_mdeu_can_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sec_mdeu_newsession(struct sec_softc *sc, struct sec_session *ses,
    struct cryptoini *enc, struct cryptoini *mac)
{

	if (mac && sec_mdeu_can_handle(mac->cri_alg))
		return (0);

	return (-1);
}