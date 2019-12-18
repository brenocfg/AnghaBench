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
struct proto_conn {int dummy; } ;
struct nv {int dummy; } ;
struct hastd_config {int hc_controladdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAST_TIMEOUT ; 
 int /*<<< orphan*/  cfgpath ; 
 int hast_proto_recv_hdr (struct proto_conn*,struct nv**) ; 
 int hast_proto_send (int /*<<< orphan*/ *,struct proto_conn*,struct nv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int nv_get_int16 (struct nv*,char*) ; 
 int /*<<< orphan*/  nv_set_error (struct nv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_error (char*,int) ; 
 int proto_client (int /*<<< orphan*/ *,int,struct proto_conn**) ; 
 int /*<<< orphan*/  proto_close (struct proto_conn*) ; 
 int proto_connect (struct proto_conn*,int /*<<< orphan*/ ) ; 
 struct hastd_config* yy_config_parse (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hastctl(struct nv *nvin, struct nv **nvout)
{
	struct hastd_config *cfg;
	struct proto_conn *conn;
	struct nv *nv;
	int error;

	cfg = yy_config_parse(cfgpath, true);
	if (cfg == NULL)
		return (-1);

	/* Setup control connection... */
	if (proto_client(NULL, cfg->hc_controladdr, &conn) == -1) {
		pjdlog_error("Unable to setup control connection to %s",
		    cfg->hc_controladdr);
		return (-1);
	}
	/* ...and connect to hastd. */
	if (proto_connect(conn, HAST_TIMEOUT) == -1) {
		pjdlog_error("Unable to connect to hastd via %s",
		    cfg->hc_controladdr);
		proto_close(conn);
		return (-1);
	}
	/* Send the command to the server... */
	if (hast_proto_send(NULL, conn, nvin, NULL, 0) == -1) {
		pjdlog_error("Unable to send command to hastd via %s",
		    cfg->hc_controladdr);
		proto_close(conn);
		return (-1);
	}
	/* ...and receive reply. */
	if (hast_proto_recv_hdr(conn, &nv) == -1) {
		pjdlog_error("cannot receive reply from hastd via %s",
		    cfg->hc_controladdr);
		proto_close(conn);
		return (-1);
	}
	proto_close(conn);
	error = nv_get_int16(nv, "error");
	if (error != 0) {
		pjdlog_error("Error %d received from hastd.", error);
		nv_free(nv);
		return (-1);
	}
	nv_set_error(nv, 0);
	*nvout = nv;
	return (0);
}