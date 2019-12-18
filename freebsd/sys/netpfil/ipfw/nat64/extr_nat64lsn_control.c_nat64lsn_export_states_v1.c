#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union nat64lsn_pgidx {int chunk; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct sockopt_data {int dummy; } ;
struct nat64lsn_state {int flags; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  proto; int /*<<< orphan*/  aport; int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; int /*<<< orphan*/  ip_dst; TYPE_3__* host; } ;
struct nat64lsn_pg {int chunks_count; TYPE_2__** states_chunk; TYPE_1__* states; } ;
struct nat64lsn_cfg {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  idle; int /*<<< orphan*/  proto; scalar_t__ flags; int /*<<< orphan*/  aport; int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; TYPE_4__ daddr; int /*<<< orphan*/  host6; } ;
typedef  TYPE_5__ ipfw_nat64lsn_state_v1 ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {struct nat64lsn_state* state; } ;
struct TYPE_6__ {struct nat64lsn_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP_STATE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREEMASK_COPY (struct nat64lsn_pg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_AGE (int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET64 (int /*<<< orphan*/ ,int) ; 
 int bitcount64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,int) ; 

__attribute__((used)) static int
nat64lsn_export_states_v1(struct nat64lsn_cfg *cfg, union nat64lsn_pgidx *idx,
    struct nat64lsn_pg *pg, struct sockopt_data *sd, uint32_t *ret_count)
{
	ipfw_nat64lsn_state_v1 *s;
	struct nat64lsn_state *state;
	uint64_t freemask;
	uint32_t i, count;

	/* validate user input */
	if (idx->chunk > pg->chunks_count - 1)
		return (EINVAL);

	FREEMASK_COPY(pg, idx->chunk, freemask);
	count = 64 - bitcount64(freemask);
	if (count == 0)
		return (0);	/* Try next PG/chunk */

	DPRINTF(DP_STATE, "EXPORT PG 0x%16jx, count %d",
	    (uintmax_t)idx->index, count);

	s = (ipfw_nat64lsn_state_v1 *)ipfw_get_sopt_space(sd,
	    count * sizeof(ipfw_nat64lsn_state_v1));
	if (s == NULL)
		return (ENOMEM);

	for (i = 0; i < 64; i++) {
		if (ISSET64(freemask, i))
			continue;
		state = pg->chunks_count == 1 ? &pg->states->state[i] :
		    &pg->states_chunk[idx->chunk]->state[i];

		s->host6 = state->host->addr;
		s->daddr.s_addr = htonl(state->ip_dst);
		s->dport = state->dport;
		s->sport = state->sport;
		s->aport = state->aport;
		s->flags = (uint8_t)(state->flags & 7);
		s->proto = state->proto;
		s->idle = GET_AGE(state->timestamp);
		s++;
	}
	*ret_count = count;
	return (0);
}