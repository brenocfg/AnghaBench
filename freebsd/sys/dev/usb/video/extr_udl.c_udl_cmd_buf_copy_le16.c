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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct udl_softc {int dummy; } ;
struct udl_cmd_buf {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int UDL_BULK_CMD_FB_COPY ; 
 int UDL_BULK_CMD_FB_WORD ; 
 int UDL_BULK_SOC ; 
 struct udl_cmd_buf* udl_cmd_buf_alloc (struct udl_softc*,int) ; 
 int /*<<< orphan*/  udl_cmd_buf_send (struct udl_softc*,struct udl_cmd_buf*) ; 
 int /*<<< orphan*/  udl_cmd_insert_int_1 (struct udl_cmd_buf*,int) ; 
 int /*<<< orphan*/  udl_cmd_insert_int_3 (struct udl_cmd_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udl_cmd_buf_copy_le16(struct udl_softc *sc, uint32_t src, uint32_t dst,
    uint8_t pixels, int flags)
{
	struct udl_cmd_buf *cb;

	cb = udl_cmd_buf_alloc(sc, flags);
	if (cb == NULL)
		return (EAGAIN);

	udl_cmd_insert_int_1(cb, UDL_BULK_SOC);
	udl_cmd_insert_int_1(cb, UDL_BULK_CMD_FB_COPY | UDL_BULK_CMD_FB_WORD);
	udl_cmd_insert_int_3(cb, dst);
	udl_cmd_insert_int_1(cb, pixels);
	udl_cmd_insert_int_3(cb, src);
	udl_cmd_buf_send(sc, cb);

	return (0);
}