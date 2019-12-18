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
typedef  int /*<<< orphan*/  tab ;

/* Variables and functions */
#define  ASCII_NBRSP 128 
 int /*<<< orphan*/  assert (int) ; 
 char const* mchars_uc2str (int) ; 

const char *
ascii_uc2str(int uc)
{
	static const char nbrsp[2] = { ASCII_NBRSP, '\0' };
	static const char *tab[] = {
	"<NUL>","<SOH>","<STX>","<ETX>","<EOT>","<ENQ>","<ACK>","<BEL>",
	"<BS>",	"\t",	"<LF>",	"<VT>",	"<FF>",	"<CR>",	"<SO>",	"<SI>",
	"<DLE>","<DC1>","<DC2>","<DC3>","<DC4>","<NAK>","<SYN>","<ETB>",
	"<CAN>","<EM>",	"<SUB>","<ESC>","<FS>",	"<GS>",	"<RS>",	"<US>",
	" ",	"!",	"\"",	"#",	"$",	"%",	"&",	"'",
	"(",	")",	"*",	"+",	",",	"-",	".",	"/",
	"0",	"1",	"2",	"3",	"4",	"5",	"6",	"7",
	"8",	"9",	":",	";",	"<",	"=",	">",	"?",
	"@",	"A",	"B",	"C",	"D",	"E",	"F",	"G",
	"H",	"I",	"J",	"K",	"L",	"M",	"N",	"O",
	"P",	"Q",	"R",	"S",	"T",	"U",	"V",	"W",
	"X",	"Y",	"Z",	"[",	"\\",	"]",	"^",	"_",
	"`",	"a",	"b",	"c",	"d",	"e",	"f",	"g",
	"h",	"i",	"j",	"k",	"l",	"m",	"n",	"o",
	"p",	"q",	"r",	"s",	"t",	"u",	"v",	"w",
	"x",	"y",	"z",	"{",	"|",	"}",	"~",	"<DEL>",
	"<80>",	"<81>",	"<82>",	"<83>",	"<84>",	"<85>",	"<86>",	"<87>",
	"<88>",	"<89>",	"<8A>",	"<8B>",	"<8C>",	"<8D>",	"<8E>",	"<8F>",
	"<90>",	"<91>",	"<92>",	"<93>",	"<94>",	"<95>",	"<96>",	"<97>",
	"<98>",	"<99>",	"<9A>",	"<9B>",	"<9C>",	"<9D>",	"<9E>",	"<9F>",
	nbrsp,	"!",	"/\bc",	"-\bL",	"o\bx",	"=\bY",	"|",	"<section>",
	"\"",	"(C)",	"_\ba",	"<<",	"~",	"",	"(R)",	"-",
	"<degree>","+-","^2",	"^3",	"'","<micro>","<paragraph>",".",
	",",	"^1",	"_\bo",	">>",	"1/4",	"1/2",	"3/4",	"?",
	"`\bA",	"'\bA",	"^\bA",	"~\bA",	"\"\bA","o\bA",	"AE",	",\bC",
	"`\bE",	"'\bE",	"^\bE",	"\"\bE","`\bI",	"'\bI",	"^\bI",	"\"\bI",
	"Dh",	"~\bN",	"`\bO",	"'\bO",	"^\bO",	"~\bO",	"\"\bO","x",
	"/\bO",	"`\bU",	"'\bU",	"^\bU",	"\"\bU","'\bY",	"Th",	"ss",
	"`\ba",	"'\ba",	"^\ba",	"~\ba",	"\"\ba","o\ba",	"ae",	",\bc",
	"`\be",	"'\be",	"^\be",	"\"\be","`\bi",	"'\bi",	"^\bi",	"\"\bi",
	"dh",	"~\bn",	"`\bo",	"'\bo",	"^\bo",	"~\bo",	"\"\bo","/",
	"/\bo",	"`\bu",	"'\bu",	"^\bu",	"\"\bu","'\by",	"th",	"\"\by",
	"A",	"a",	"A",	"a",	"A",	"a",	"'\bC",	"'\bc",
	"^\bC",	"^\bc",	"C",	"c",	"C",	"c",	"D",	"d",
	"/\bD",	"/\bd",	"E",	"e",	"E",	"e",	"E",	"e",
	"E",	"e",	"E",	"e",	"^\bG",	"^\bg",	"G",	"g",
	"G",	"g",	",\bG",	",\bg",	"^\bH",	"^\bh",	"/\bH",	"/\bh",
	"~\bI",	"~\bi",	"I",	"i",	"I",	"i",	"I",	"i",
	"I",	"i",	"IJ",	"ij",	"^\bJ",	"^\bj",	",\bK",	",\bk",
	"q",	"'\bL",	"'\bl",	",\bL",	",\bl",	"L",	"l",	"L",
	"l",	"/\bL",	"/\bl",	"'\bN",	"'\bn",	",\bN",	",\bn",	"N",
	"n",	"'n",	"Ng",	"ng",	"O",	"o",	"O",	"o",
	"O",	"o",	"OE",	"oe",	"'\bR",	"'\br",	",\bR",	",\br",
	"R",	"r",	"'\bS",	"'\bs",	"^\bS",	"^\bs",	",\bS",	",\bs",
	"S",	"s",	",\bT",	",\bt",	"T",	"t",	"/\bT",	"/\bt",
	"~\bU",	"~\bu",	"U",	"u",	"U",	"u",	"U",	"u",
	"U",	"u",	"U",	"u",	"^\bW",	"^\bw",	"^\bY",	"^\by",
	"\"\bY","'\bZ",	"'\bz",	"Z",	"z",	"Z",	"z",	"s",
	"b",	"B",	"B",	"b",	"6",	"6",	"O",	"C",
	"c",	"D",	"D",	"D",	"d",	"d",	"3",	"@",
	"E",	"F",	",\bf",	"G",	"G",	"hv",	"I",	"/\bI",
	"K",	"k",	"/\bl",	"l",	"W",	"N",	"n",	"~\bO",
	"O",	"o",	"OI",	"oi",	"P",	"p",	"YR",	"2",
	"2",	"SH",	"sh",	"t",	"T",	"t",	"T",	"U",
	"u",	"Y",	"V",	"Y",	"y",	"/\bZ",	"/\bz",	"ZH",
	"ZH",	"zh",	"zh",	"/\b2",	"5",	"5",	"ts",	"w",
	"|",	"||",	"|=",	"!",	"DZ",	"Dz",	"dz",	"LJ",
	"Lj",	"lj",	"NJ",	"Nj",	"nj",	"A",	"a",	"I",
	"i",	"O",	"o",	"U",	"u",	"U",	"u",	"U",
	"u",	"U",	"u",	"U",	"u",	"@",	"A",	"a",
	"A",	"a",	"AE",	"ae",	"/\bG",	"/\bg",	"G",	"g",
	"K",	"k",	"O",	"o",	"O",	"o",	"ZH",	"zh",
	"j",	"DZ",	"Dz",	"dz",	"'\bG",	"'\bg",	"HV",	"W",
	"`\bN",	"`\bn",	"A",	"a",	"'\bAE","'\bae","O",	"o"};

	assert(uc >= 0);
	if ((size_t)uc < sizeof(tab)/sizeof(tab[0]))
		return tab[uc];
	return mchars_uc2str(uc);
}