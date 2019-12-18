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
typedef  unsigned long uLong ;
struct ieee80211_frame {int* i_fc; unsigned char* i_addr3; unsigned char* i_addr2; unsigned char* i_addr1; } ;
struct ether_header {int /*<<< orphan*/  ether_shost; int /*<<< orphan*/  ether_dhost; } ;
typedef  int /*<<< orphan*/  paths ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 char* DICT_PATH ; 
 int IEEE80211_FC1_DIR_FROMDS ; 
 int IEEE80211_FC1_DIR_TODS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 unsigned char* Z_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 unsigned long crc32 (unsigned long,unsigned char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  hexdump (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  tapfd ; 
 int /*<<< orphan*/  time_print (char*,...) ; 
 int write (int /*<<< orphan*/ ,unsigned char*,int) ; 

void try_dictionary(struct ieee80211_frame* wh, int len) {
	unsigned char *body;
	char path[52];
	char paths[3][3];
	int i;
	int fd, rd;
	unsigned char packet[4096];
	int dlen;
	struct ether_header* eh;
	uLong crc;
	unsigned long *pcrc;
	unsigned char* dmac, *smac;

	assert (len < sizeof(packet) + sizeof(*eh));

	body = (unsigned char*) wh + sizeof(*wh);

	for (i = 0; i < 3; i++)
		snprintf(paths[i], sizeof(paths[i]), "%.2X", body[i]);

	sprintf(path, "%s/%s/%s/%s", DICT_PATH, paths[0], paths[1], paths[2]);

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return;

	rd = read(fd, &packet[6], sizeof(packet)-6);
	if (rd == -1) {
		perror("read()");
		exit(1);
	}
	close(fd);


	dlen = len - sizeof(*wh) - 4;
	if (dlen > rd) {
		printf("\n");
		time_print("Had PRGA (%s) but too little (%d/%d)\n", path, rd,
		dlen);
		return;
	}

	body += 4;
	for (i = 0; i < dlen; i++)
		packet[6+i] ^= body[i];

	dlen -= 4;
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, &packet[6], dlen);
	pcrc = (unsigned long*) (&packet[6+dlen]);

	if (*pcrc != crc) {
		printf("\n");
		time_print("HAD PRGA (%s) checksum mismatch! (%x %x)\n",
			   path, *pcrc, crc);
		return;
	}

	// fill ethernet header
	eh = (struct ether_header*) packet;
	if (wh->i_fc[1] & IEEE80211_FC1_DIR_FROMDS)
		smac = wh->i_addr3;
	else
		smac = wh->i_addr2;

	if (wh->i_fc[1] & IEEE80211_FC1_DIR_TODS)
		dmac = wh->i_addr3;
	else
		dmac = wh->i_addr1;

	memcpy(eh->ether_dhost, dmac, 6);
	memcpy(eh->ether_shost, smac, 6);
	// ether type should be there from llc

	dlen -= 8; // llc
	dlen += sizeof(*eh);

#if 0
	printf("\n");
	time_print("Decrypted packet [%d bytes]!!! w00t\n", dlen);
	hexdump(packet, dlen);
#endif

	rd = write(tapfd, packet, dlen);
	if (rd == -1) {
		perror("write()");
		exit(1);
	}
	if (rd != dlen) {
		printf("Wrote %d / %d\n", rd, dlen);
		exit(1);
	}
}