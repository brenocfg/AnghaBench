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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  typestr ;
struct auth_chunk {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  dname_pkt_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ *,char*) ; 
 size_t pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_init_frm_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_wire2str_type_buf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*,int,char*,char*) ; 

__attribute__((used)) static void
log_rrlist_position(const char* label, struct auth_chunk* rr_chunk,
	uint8_t* rr_dname, uint16_t rr_type, size_t rr_counter)
{
	sldns_buffer pkt;
	size_t dlen;
	uint8_t buf[256];
	char str[256];
	char typestr[32];
	sldns_buffer_init_frm_data(&pkt, rr_chunk->data, rr_chunk->len);
	sldns_buffer_set_position(&pkt, (size_t)(rr_dname -
		sldns_buffer_begin(&pkt)));
	if((dlen=pkt_dname_len(&pkt)) == 0) return;
	if(dlen >= sizeof(buf)) return;
	dname_pkt_copy(&pkt, buf, rr_dname);
	dname_str(buf, str);
	(void)sldns_wire2str_type_buf(rr_type, typestr, sizeof(typestr));
	verbose(VERB_ALGO, "%s at[%d] %s %s", label, (int)rr_counter,
		str, typestr);
}