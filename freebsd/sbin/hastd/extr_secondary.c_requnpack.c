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
typedef  int const uintmax_t ;
typedef  int uint64_t ;
struct nv {int dummy; } ;
struct hio {int hio_cmd; int hio_error; scalar_t__ hio_seq; int hio_offset; int hio_length; int /*<<< orphan*/  hio_memsync; } ;
struct hast_resource {int hr_local_sectorsize; int /*<<< orphan*/  hr_datasize; } ;

/* Variables and functions */
 void* EINVAL ; 
#define  HIO_DELETE 132 
#define  HIO_FLUSH 131 
#define  HIO_KEEPALIVE 130 
#define  HIO_READ 129 
#define  HIO_WRITE 128 
 int MAXPHYS ; 
 int /*<<< orphan*/  nv_error (struct nv*) ; 
 int /*<<< orphan*/  nv_exists (struct nv*,char*) ; 
 void* nv_get_uint64 (struct nv*,char*) ; 
 int nv_get_uint8 (struct nv*,char*) ; 
 int /*<<< orphan*/  pjdlog_error (char*,...) ; 

__attribute__((used)) static int
requnpack(struct hast_resource *res, struct hio *hio, struct nv *nv)
{

	hio->hio_cmd = nv_get_uint8(nv, "cmd");
	if (hio->hio_cmd == 0) {
		pjdlog_error("Header contains no 'cmd' field.");
		hio->hio_error = EINVAL;
		goto end;
	}
	if (hio->hio_cmd != HIO_KEEPALIVE) {
		hio->hio_seq = nv_get_uint64(nv, "seq");
		if (hio->hio_seq == 0) {
			pjdlog_error("Header contains no 'seq' field.");
			hio->hio_error = EINVAL;
			goto end;
		}
	}
	switch (hio->hio_cmd) {
	case HIO_FLUSH:
	case HIO_KEEPALIVE:
		break;
	case HIO_WRITE:
		hio->hio_memsync = nv_exists(nv, "memsync");
		/* FALLTHROUGH */
	case HIO_READ:
	case HIO_DELETE:
		hio->hio_offset = nv_get_uint64(nv, "offset");
		if (nv_error(nv) != 0) {
			pjdlog_error("Header is missing 'offset' field.");
			hio->hio_error = EINVAL;
			goto end;
		}
		hio->hio_length = nv_get_uint64(nv, "length");
		if (nv_error(nv) != 0) {
			pjdlog_error("Header is missing 'length' field.");
			hio->hio_error = EINVAL;
			goto end;
		}
		if (hio->hio_length == 0) {
			pjdlog_error("Data length is zero.");
			hio->hio_error = EINVAL;
			goto end;
		}
		if (hio->hio_cmd != HIO_DELETE && hio->hio_length > MAXPHYS) {
			pjdlog_error("Data length is too large (%ju > %ju).",
			    (uintmax_t)hio->hio_length, (uintmax_t)MAXPHYS);
			hio->hio_error = EINVAL;
			goto end;
		}
		if ((hio->hio_offset % res->hr_local_sectorsize) != 0) {
			pjdlog_error("Offset %ju is not multiple of sector size.",
			    (uintmax_t)hio->hio_offset);
			hio->hio_error = EINVAL;
			goto end;
		}
		if ((hio->hio_length % res->hr_local_sectorsize) != 0) {
			pjdlog_error("Length %ju is not multiple of sector size.",
			    (uintmax_t)hio->hio_length);
			hio->hio_error = EINVAL;
			goto end;
		}
		if (hio->hio_offset + hio->hio_length >
		    (uint64_t)res->hr_datasize) {
			pjdlog_error("Data offset is too large (%ju > %ju).",
			    (uintmax_t)(hio->hio_offset + hio->hio_length),
			    (uintmax_t)res->hr_datasize);
			hio->hio_error = EINVAL;
			goto end;
		}
		break;
	default:
		pjdlog_error("Header contains invalid 'cmd' (%hhu).",
		    hio->hio_cmd);
		hio->hio_error = EINVAL;
		goto end;
	}
	hio->hio_error = 0;
end:
	return (hio->hio_error);
}