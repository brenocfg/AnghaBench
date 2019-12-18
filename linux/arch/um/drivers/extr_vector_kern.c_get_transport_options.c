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
struct arglist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANS_HYBRID ; 
 int /*<<< orphan*/  TRANS_HYBRID_LEN ; 
 int /*<<< orphan*/  TRANS_RAW ; 
 int /*<<< orphan*/  TRANS_RAW_LEN ; 
 int /*<<< orphan*/  TRANS_TAP ; 
 int /*<<< orphan*/  TRANS_TAP_LEN ; 
 int VECTOR_BPF ; 
 int VECTOR_QDISC_BYPASS ; 
 int VECTOR_RX ; 
 int VECTOR_TX ; 
 scalar_t__ kstrtoul (char*,int,long*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* uml_vector_fetch_arg (struct arglist*,char*) ; 

__attribute__((used)) static int get_transport_options(struct arglist *def)
{
	char *transport = uml_vector_fetch_arg(def, "transport");
	char *vector = uml_vector_fetch_arg(def, "vec");

	int vec_rx = VECTOR_RX;
	int vec_tx = VECTOR_TX;
	long parsed;

	if (vector != NULL) {
		if (kstrtoul(vector, 10, &parsed) == 0) {
			if (parsed == 0) {
				vec_rx = 0;
				vec_tx = 0;
			}
		}
	}


	if (strncmp(transport, TRANS_TAP, TRANS_TAP_LEN) == 0)
		return 0;
	if (strncmp(transport, TRANS_HYBRID, TRANS_HYBRID_LEN) == 0)
		return (vec_rx | VECTOR_BPF);
	if (strncmp(transport, TRANS_RAW, TRANS_RAW_LEN) == 0)
		return (vec_rx | vec_tx | VECTOR_QDISC_BYPASS);
	return (vec_rx | vec_tx);
}