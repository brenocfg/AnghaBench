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
typedef  int /*<<< orphan*/  uint8_t ;
struct t4_data {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int INTR_OK ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SLEEP_OK ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t4_load_cfg (struct adapter*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
load_cfg(struct adapter *sc, struct t4_data *cfg)
{
	int rc;
	uint8_t *cfg_data = NULL;

	rc = begin_synchronized_op(sc, NULL, SLEEP_OK | INTR_OK, "t4ldcf");
	if (rc)
		return (rc);

	if (cfg->len == 0) {
		/* clear */
		rc = -t4_load_cfg(sc, NULL, 0);
		goto done;
	}

	cfg_data = malloc(cfg->len, M_CXGBE, M_WAITOK);
	if (cfg_data == NULL) {
		rc = ENOMEM;
		goto done;
	}

	rc = copyin(cfg->data, cfg_data, cfg->len);
	if (rc == 0)
		rc = -t4_load_cfg(sc, cfg_data, cfg->len);

	free(cfg_data, M_CXGBE);
done:
	end_synchronized_op(sc, 0);
	return (rc);
}