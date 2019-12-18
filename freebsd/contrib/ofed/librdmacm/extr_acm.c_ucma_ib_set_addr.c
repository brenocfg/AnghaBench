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
struct sockaddr_ib {int /*<<< orphan*/  sib_addr; void* sib_flowinfo; int /*<<< orphan*/  sib_pkey; void* sib_family; } ;
struct sockaddr {int dummy; } ;
struct rdma_addrinfo {int ai_src_len; int ai_dst_len; struct sockaddr* ai_dst_addr; struct sockaddr* ai_src_addr; int /*<<< orphan*/  ai_port_space; scalar_t__ ai_route; } ;
struct ibv_path_record {int /*<<< orphan*/  dgid; int /*<<< orphan*/  flowlabel_hoplimit; int /*<<< orphan*/  pkey; int /*<<< orphan*/  sgid; } ;
struct ibv_path_data {struct ibv_path_record path; } ;

/* Variables and functions */
 void* AF_IB ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 struct sockaddr_ib* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct sockaddr_ib*) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucma_set_sid (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr_ib*) ; 

__attribute__((used)) static int ucma_ib_set_addr(struct rdma_addrinfo *ib_rai,
			    struct rdma_addrinfo *rai)
{
	struct sockaddr_ib *src, *dst;
	struct ibv_path_record *path;

	src = calloc(1, sizeof(*src));
	if (!src)
		return ERR(ENOMEM);

	dst = calloc(1, sizeof(*dst));
	if (!dst) {
		free(src);
		return ERR(ENOMEM);
	}

	path = &((struct ibv_path_data *) ib_rai->ai_route)->path;

	src->sib_family = AF_IB;
	src->sib_pkey = path->pkey;
	src->sib_flowinfo = htobe32(be32toh(path->flowlabel_hoplimit) >> 8);
	memcpy(&src->sib_addr, &path->sgid, 16);
	ucma_set_sid(ib_rai->ai_port_space, rai->ai_src_addr, src);

	dst->sib_family = AF_IB;
	dst->sib_pkey = path->pkey;
	dst->sib_flowinfo = htobe32(be32toh(path->flowlabel_hoplimit) >> 8);
	memcpy(&dst->sib_addr, &path->dgid, 16);
	ucma_set_sid(ib_rai->ai_port_space, rai->ai_dst_addr, dst);

	ib_rai->ai_src_addr = (struct sockaddr *) src;
	ib_rai->ai_src_len = sizeof(*src);

	ib_rai->ai_dst_addr = (struct sockaddr *) dst;
	ib_rai->ai_dst_len = sizeof(*dst);

	return 0;
}