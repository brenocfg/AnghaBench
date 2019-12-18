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
struct TYPE_2__ {int /*<<< orphan*/  class; int /*<<< orphan*/  locale; scalar_t__ reserved; } ;
union mrsas_evt_class_locale {int /*<<< orphan*/  word; TYPE_1__ members; } ;
struct mrsas_softc {int dummy; } ;
struct mrsas_evt_log_info {scalar_t__ newest_seq_num; } ;
typedef  int /*<<< orphan*/  eli ;

/* Variables and functions */
 int /*<<< orphan*/  MR_EVT_CLASS_DEBUG ; 
 int /*<<< orphan*/  MR_EVT_LOCALE_ALL ; 
 int /*<<< orphan*/  memset (struct mrsas_evt_log_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mrsas_get_seq_num (struct mrsas_softc*,struct mrsas_evt_log_info*) ; 
 int mrsas_register_aen (struct mrsas_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mrsas_start_aen(struct mrsas_softc *sc)
{
	struct mrsas_evt_log_info eli;
	union mrsas_evt_class_locale class_locale;


	/* Get the latest sequence number from FW */

	memset(&eli, 0, sizeof(eli));

	if (mrsas_get_seq_num(sc, &eli))
		return -1;

	/* Register AEN with FW for latest sequence number plus 1 */
	class_locale.members.reserved = 0;
	class_locale.members.locale = MR_EVT_LOCALE_ALL;
	class_locale.members.class = MR_EVT_CLASS_DEBUG;

	return mrsas_register_aen(sc, eli.newest_seq_num + 1,
	    class_locale.word);

}