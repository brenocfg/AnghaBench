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
struct nv {int dummy; } ;
struct hast_resource {scalar_t__ hr_role; int /*<<< orphan*/  hr_ctrl; scalar_t__ hr_metaflush; int /*<<< orphan*/  hr_exec; scalar_t__ hr_timeout; scalar_t__ hr_compression; scalar_t__ hr_checksum; scalar_t__ hr_replication; int /*<<< orphan*/  hr_sourceaddr; int /*<<< orphan*/  hr_remoteaddr; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_RELOAD ; 
 scalar_t__ HAST_ROLE_PRIMARY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int hast_proto_recv_hdr (int /*<<< orphan*/ ,struct nv**) ; 
 int hast_proto_send (struct hast_resource const*,int /*<<< orphan*/ ,struct nv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_add_int32 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nv_add_string (struct nv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nv_add_uint8 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 struct nv* nv_alloc () ; 
 scalar_t__ nv_error (struct nv*) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int nv_get_int16 (struct nv*,char*) ; 
 int /*<<< orphan*/  pjdlog_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_error (char*) ; 

__attribute__((used)) static void
resource_reload(const struct hast_resource *res)
{
	struct nv *nvin, *nvout;
	int error;

	PJDLOG_ASSERT(res->hr_role == HAST_ROLE_PRIMARY);

	nvout = nv_alloc();
	nv_add_uint8(nvout, CONTROL_RELOAD, "cmd");
	nv_add_string(nvout, res->hr_remoteaddr, "remoteaddr");
	nv_add_string(nvout, res->hr_sourceaddr, "sourceaddr");
	nv_add_int32(nvout, (int32_t)res->hr_replication, "replication");
	nv_add_int32(nvout, (int32_t)res->hr_checksum, "checksum");
	nv_add_int32(nvout, (int32_t)res->hr_compression, "compression");
	nv_add_int32(nvout, (int32_t)res->hr_timeout, "timeout");
	nv_add_string(nvout, res->hr_exec, "exec");
	nv_add_int32(nvout, (int32_t)res->hr_metaflush, "metaflush");
	if (nv_error(nvout) != 0) {
		nv_free(nvout);
		pjdlog_error("Unable to allocate header for reload message.");
		return;
	}
	if (hast_proto_send(res, res->hr_ctrl, nvout, NULL, 0) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to send reload message");
		nv_free(nvout);
		return;
	}
	nv_free(nvout);

	/* Receive response. */
	if (hast_proto_recv_hdr(res->hr_ctrl, &nvin) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to receive reload reply");
		return;
	}
	error = nv_get_int16(nvin, "error");
	nv_free(nvin);
	if (error != 0) {
		pjdlog_common(LOG_ERR, 0, error, "Reload failed");
		return;
	}
}